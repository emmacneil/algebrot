#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "fractal_widget.hpp"

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    FractalWidget *fractalWidget;
    QHBoxLayout *mainLayout;
    QLineEdit *aLineEdit;
    QLineEdit *bLineEdit;
    QLineEdit *cLineEdit;
    QLineEdit *xLineEdit;
    QLineEdit *yLineEdit;
    QLineEdit *zLineEdit;
    QLineEdit *scaleLineEdit;
    QPushButton *resetButton;

    void resetFractal();
    void updateFractal();
    void updateViewLineEdits(QVector3D center, float scale);
};

#endif // MAINWINDOW_HPP
