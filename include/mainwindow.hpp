#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "fractal_widget.hpp"

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    FractalWidget *fractalWidget;
    QLineEdit *reLineEdit;
    QLineEdit *imLineEdit;
    QLineEdit *scaleLineEdit;
    QPushButton *resetButton;
    void resetFractal();
};

#endif // MAINWINDOW_HPP
