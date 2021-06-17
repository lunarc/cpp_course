#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Manipulate the position, size and title
    // of the main window

    this->resize(640,480);
    this->setWindowTitle("Super Simulator 1.0");
    this->move(50,50);

    this->setWindowState(Qt::WindowMaximized);
    //this->setWindowState(Qt::WindowFullScreen);
}

MainWindow::~MainWindow()
{
    delete ui;
}
