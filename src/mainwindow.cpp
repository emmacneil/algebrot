#include "mainwindow.hpp"

#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Algebrot");

    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    widget->setLayout(mainLayout);

    // Left side of main window
    // Should be two group boxes, one above the other.
    // The upper group box allows the user to edit the modulus polynomial
    // The lower group box allows the user to control the view
    QWidget *leftWidget = new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftWidget->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    leftWidget->setLayout(leftLayout);
    mainLayout->addWidget(leftWidget);

    QGroupBox *modulusGroupBox = new QGroupBox(tr("Modulus"));
    //modulusGroupBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    leftLayout->addWidget(modulusGroupBox);

    QFormLayout *modulusLayout = new QFormLayout;
    aLineEdit = new QLineEdit;
    bLineEdit = new QLineEdit;
    cLineEdit = new QLineEdit;
    aLineEdit->setEnabled(false);
    bLineEdit->setEnabled(false);
    cLineEdit->setEnabled(false);
    modulusLayout->addRow(tr("A:"), aLineEdit);
    modulusLayout->addRow(tr("B:"), bLineEdit);
    modulusLayout->addRow(tr("C:"), cLineEdit);
    modulusGroupBox->setLayout(modulusLayout);

    QGroupBox *viewGroupBox = new QGroupBox(tr("View"));
    //viewGroupBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    leftLayout->addWidget(viewGroupBox);

    QFormLayout *viewLayout = new QFormLayout;
    xLineEdit = new QLineEdit;
    yLineEdit = new QLineEdit;
    zLineEdit = new QLineEdit;
    zLineEdit->setEnabled(false);
    scaleLineEdit = new QLineEdit;
    viewLayout->addRow(tr("X:"), xLineEdit);
    viewLayout->addRow(tr("Y:"), yLineEdit);
    viewLayout->addRow(tr("Z:"), zLineEdit);
    viewLayout->addRow(tr("Scale:"), scaleLineEdit);
    viewGroupBox->setLayout(viewLayout);

    resetButton = new QPushButton(tr("&Reset"));
    leftLayout->addWidget(resetButton);

    // Right side of the main window
    // Houses the OpenGL widget that renders the fractal
    fractalWidget = new FractalWidget;
    mainLayout->addWidget(fractalWidget);

    aLineEdit->setText(QString::number(0.0f));
    bLineEdit->setText(QString::number(1.0f));
    cLineEdit->setText(QString::number(0.0f));
    xLineEdit->setText(QString::number(0.0f));
    yLineEdit->setText(QString::number(0.0f));
    zLineEdit->setText(QString::number(0.0f));
    connect(aLineEdit, &QLineEdit::editingFinished, this, &MainWindow::updateFractal);
    connect(bLineEdit, &QLineEdit::editingFinished, this, &MainWindow::updateFractal);
    connect(cLineEdit, &QLineEdit::editingFinished, this, &MainWindow::updateFractal);
    connect(xLineEdit, &QLineEdit::editingFinished, this, &MainWindow::updateFractal);
    connect(yLineEdit, &QLineEdit::editingFinished, this, &MainWindow::updateFractal);
    connect(zLineEdit, &QLineEdit::editingFinished, this, &MainWindow::updateFractal);
    connect(scaleLineEdit, &QLineEdit::editingFinished, this, &MainWindow::updateFractal);
    connect(fractalWidget, &FractalWidget::changed, this, &MainWindow::updateViewLineEdits);
    connect(resetButton, &QPushButton::clicked, fractalWidget, &FractalWidget::reset);

    showMaximized();
}

void MainWindow::resetFractal()
{
    fractalWidget->reset();
    fractalWidget->update();
}

void MainWindow::updateFractal()
{
    float a, b, c, x, y, z, s;
    a = aLineEdit->text().toFloat();
    b = bLineEdit->text().toFloat();
    c = cLineEdit->text().toFloat();
    x = xLineEdit->text().toFloat();
    y = yLineEdit->text().toFloat();
    z = zLineEdit->text().toFloat();
    s = scaleLineEdit->text().toFloat();
    fractalWidget->setModulus(QVector3D(a, b, c));
    fractalWidget->setCenter(QVector3D(x, y, z));
    fractalWidget->setScale(s);
}

void MainWindow::updateViewLineEdits(QVector3D center, float scale)
{
    xLineEdit->setText(QString::number(center.x()));
    yLineEdit->setText(QString::number(center.y()));
    zLineEdit->setText(QString::number(center.z()));
    scaleLineEdit->setText(QString::number(scale));
}
