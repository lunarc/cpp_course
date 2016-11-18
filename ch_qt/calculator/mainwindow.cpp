#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScriptEngine>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_evalButton_clicked()
{
    QScriptEngine engine;
    QScriptValue value = engine.evaluate(ui->expressionEdit->text());
    ui->resultEdit->setText(value.toString());
}
