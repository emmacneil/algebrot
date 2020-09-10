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

    QGroupBox *groupBox = new QGroupBox(tr("Controls"));
    groupBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    mainLayout->addWidget(groupBox);

    QVBoxLayout *groupBoxLayout = new QVBoxLayout;
    groupBox->setLayout(groupBoxLayout);

    QFormLayout *formLayout = new QFormLayout;
    reLineEdit = new QLineEdit;
    imLineEdit = new QLineEdit;
    scaleLineEdit = new QLineEdit;
    formLayout->addRow(tr("Re:"), reLineEdit);
    formLayout->addRow(tr("Im:"), imLineEdit);
    formLayout->addRow(tr("Scale:"), scaleLineEdit);
    groupBoxLayout->addLayout(formLayout);

    resetButton = new QPushButton(tr("&Reset"));
    groupBoxLayout->addWidget(resetButton);

    fractalWidget = new FractalWidget;
    mainLayout->addWidget(fractalWidget);

    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetFractal);

    showMaximized();
}

void MainWindow::resetFractal()
{
    fractalWidget->reset();
    fractalWidget->update();
}
