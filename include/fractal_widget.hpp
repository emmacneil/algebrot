#ifndef FRACTALWIDGET_HPP
#define FRACTALWIDGET_HPP

#include <QMouseEvent>

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

class FractalWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    FractalWidget();
    ~FractalWidget();

    QVector3D getCenter() const;
    float getScale() const;
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void reset();
    void setCenter(QVector3D c);
    void setModulus(QVector3D m);
    void setScale(float s);

protected:
    int glslBottomLeftLocation;
    int glslScaleLocation;
    int glslIterLocation;

    QVector3D center;
    QVector3D modulus;
    float centerRe; // Value of complex number in middle of viewport
    float centerIm;
    float scale; // Difference between complex numbers of two orthogonally adjacent pixels

    QOpenGLBuffer vertexBufferObject;
    QOpenGLShaderProgram *shaderProgram;
    QOpenGLVertexArrayObject vertexArrayObject;

    QWidget *parent;

    void mousePressEvent(QMouseEvent *e) override;

    void printGLVersion();
    void printGLSLVersion();

signals:
    void changed(QVector3D center, float scale);
};

#endif // FRACTALWIDGET_HPP
