#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pressMeButton, SIGNAL(clicked()), this, SLOT(onButtonPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonPressed()
{
    qDebug() << "Ouch!";
}

void MainWindow::on_pressMeButton_clicked()
{
    qDebug() << "Ouch again!";
}
