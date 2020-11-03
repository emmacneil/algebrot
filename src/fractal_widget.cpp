#include "fractal_widget.hpp"

#include <fstream>
#include <sstream>

#include <QDebug>
#include <QOpenGLFunctions>

FractalWidget::FractalWidget()
{
}

FractalWidget::~FractalWidget()
{
}

QVector3D FractalWidget::getCenter() const
{
    return center;
}

float FractalWidget::getScale() const
{
    return scale;
}

void FractalWidget::initializeGL()
{
    printGLVersion();
    printGLSLVersion();

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    f->glEnable(GL_TEXTURE_1D);

    shaderProgram = new QOpenGLShaderProgram;
    if (!shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/glsl/shader.vert"))
        qDebug() << shaderProgram->log();
    if (shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/glsl/algebrot3d.frag"))
    if (!shaderProgram->link())
        qDebug() << shaderProgram->log();

    shaderProgram->bind();
    glslBottomLeftLocation = shaderProgram->uniformLocation("bottomLeft");
    glslModulusLocation = shaderProgram->uniformLocation("modulus");
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

    texture = new QOpenGLTexture(QImage(":/img/gradient.png"));
    if (!texture->create())
        qDebug() << "Could not create texture";

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
        float cornerX = center.x() - widgetW * scale / 2.0f;
        float cornerY = center.y() - widgetH * scale / 2.0f;
        center[0] = cornerX + scale*mouseX;
        center[1] = cornerY + scale*mouseY;
    }

    // If it was a left click, also zoom in
    if (e->button() & Qt::LeftButton)
        scale /= 2.0f;

    // If it was a right click, also zoom out.
    if (e->button() & Qt::RightButton)
        scale *= 2.0f;

    update();
    emit changed(center, scale);
}

void FractalWidget::paintGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT);

    float x = center.x() - width()*scale/2.0f;
    float y = center.y() - height()*scale/2.0f;
    float z = center.z();

    QOpenGLVertexArrayObject::Binder vertexArrayObjectBinder(&vertexArrayObject);
    shaderProgram->bind();
    texture->bind(0);

    shaderProgram->setUniformValue(glslBottomLeftLocation, x, y, z);
    shaderProgram->setUniformValue(glslModulusLocation, modulus);
    shaderProgram->setUniformValue(glslScaleLocation, scale);
    shaderProgram->setUniformValue(glslIterLocation, 1000);

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

void FractalWidget::reset()
{
    float w = width();
    float h = height();
    center[0] = 0.0f;
    center[1] = 0.0f;
    center[2] = 0.0f;
    scale = 4.0f/(w < h ? w : h);
    update();
    emit changed(center, scale);
}

void FractalWidget::setCenter(QVector3D c)
{
    center = c;
    update();
    emit changed(center, scale);
}

void FractalWidget::resizeGL(int w, int h)
{
    // ...
}

void FractalWidget::setModulus(QVector3D m)
{
    modulus = m;
    update();
    emit changed(center, scale);
}

void FractalWidget::setScale(float s)
{
    scale = s;
    update();
    emit changed(center, scale);
}
