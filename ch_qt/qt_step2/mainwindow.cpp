#include "mainwindow.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
{
    // Set the window title
    setWindowTitle("My Text Editor");
    setGeometry(100, 100, 800, 600);
}
