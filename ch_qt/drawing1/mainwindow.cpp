#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::toDouble(const QString& str, double defValue)
{
    bool ok;
    double value = str.toDouble(&ok);
    if (ok)
        return value;
    else
        return defValue;
}
