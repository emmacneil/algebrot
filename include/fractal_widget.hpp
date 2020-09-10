#ifndef FRACTALWIDGET_HPP
#define FRACTALWIDGET_HPP

#include <QMouseEvent>

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

class FractalWidget : public QOpenGLWidget
{
public:
    FractalWidget();
    ~FractalWidget();

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    void reset();

protected:
    int glslBottomLeftLocation;
    int glslScaleLocation;
    int glslIterLocation;

    float centerRe; // Value of complex number in middle of viewport
    float centerIm;
    float scale; // Difference between complex numbers of two orthogonally adjacent pixels

    QOpenGLBuffer vertexBufferObject;
    QOpenGLShaderProgram *shaderProgram;
    QOpenGLVertexArrayObject vertexArrayObject;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;

    void printGLVersion();
    void printGLSLVersion();
    void recenter(float re, float im);


};

#endif // FRACTALWIDGET_HPP
