#include "fractal_widget.hpp"
#include "shader.hpp"

#include <fstream>
#include <sstream>

#include <QDebug>
#include <QOpenGLFunctions>

FractalWidget::FractalWidget()
{
    int w = width();
    int h = height();
}

FractalWidget::~FractalWidget()
{
}

void FractalWidget::initializeGL()
{
    printGLVersion();
    printGLSLVersion();

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    shaderProgram = new QOpenGLShaderProgram;
    if (!shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/glsl/shader.vert"))
        qDebug() << shaderProgram->log();
    if (shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/glsl/mandelbrot.frag"))
        qDebug() << shaderProgram->log();
    if (!shaderProgram->link())
        qDebug() << shaderProgram->log();

    shaderProgram->bind();
    glslBottomLeftLocation = shaderProgram->uniformLocation("bottomLeft");
    glslScaleLocation = shaderProgram->uniformLocation("scale");
    glslIterLocation = shaderProgram->uniformLocation("iter");

    vertexArrayObject.create();
    QOpenGLVertexArrayObject::Binder vertexArrayObjectBinder(&vertexArrayObject);

    float vertices[] = {1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f};
    vertexBufferObject.create();
    vertexBufferObject.bind();
    vertexBufferObject.allocate(vertices, sizeof(vertices));

    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);

    vertexBufferObject.release();
    shaderProgram->release();

    reset();
}

void FractalWidget::mousePressEvent(QMouseEvent *e)
{
    // If the left or right mouse button was clicked, recenter the fractal on where the click occurred
    if (e->button() & (Qt::LeftButton | Qt::RightButton))
    {
        // Get coordinates of location where mouse was click.
        // This will be in pixels relative to the top-left corner of the widget
        // But positive y is in the downward direction.
        // Convert this into fractal coordinates.
        QPoint p = e->pos();
        float widgetW = (float)width();
        float widgetH = (float)height();
        float mouseX = (float)p.x();
        float mouseY = widgetH - (float)p.y();
        float cornerRe = centerRe - widgetW * scale / 2.0f;
        float cornerIm = centerIm - widgetH * scale / 2.0f;
        centerRe = cornerRe + scale*mouseX;
        centerIm = cornerIm + scale*mouseY;
    }

    // If it was a left click, also zoom in
    if (e->button() & Qt::LeftButton)
        scale /= 2.0f;

    // If it was a right click, also zoom out.
    if (e->button() & Qt::RightButton)
        scale *= 2.0f;

    update();
}

void FractalWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    QOpenGLWidget::mouseDoubleClickEvent(e);
    scale /= 2.0f;
    update();
}

void FractalWidget::paintGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT);

    QOpenGLVertexArrayObject::Binder vertexArrayObjectBinder(&vertexArrayObject);
    shaderProgram->bind();
    // set uniform values with shaderProgram->setUniformValue(...)
    float re = centerRe - width()*scale/2.0f;
    float im = centerIm - height()*scale/2.0f;
    shaderProgram->setUniformValue(glslBottomLeftLocation, re, im);
    shaderProgram->setUniformValue(glslScaleLocation, scale);
    shaderProgram->setUniformValue(glslIterLocation, 200);
    f->glDrawArrays(GL_QUADS, 0, 4);
    shaderProgram->release();
}

void FractalWidget::printGLVersion()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    const GLubyte *bytes = f->glGetString(GL_VERSION);
    QString str = "";
    for (int i = 0; bytes[i] != 0; i++)
    {
        str += (char)bytes[i];
    }
    qDebug() << "Using GL version " << str;
}

void FractalWidget::printGLSLVersion()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    const GLubyte *bytes = f->glGetString(GL_SHADING_LANGUAGE_VERSION);
    QString str = "";
    for (int i = 0; bytes[i] != 0; i++)
    {
        str += (char)bytes[i];
    }
    qDebug() << "Using GLSL version " << str;
}

void FractalWidget::recenter(float re, float im)
{
    centerRe = re;
    centerIm = im;
}

void FractalWidget::reset()
{
    float w = width();
    float h = height();
    centerRe = 0.0f;
    centerIm = 0.0f;
    scale = 4.0f/(w < h ? w : h);
}

void FractalWidget::resizeGL(int w, int h)
{
    // ...
}
