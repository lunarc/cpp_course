#include "mainwindow.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    // Set the window title
    setWindowTitle("My First Qt Application");
    setGeometry(100, 100, 800, 600);
}
