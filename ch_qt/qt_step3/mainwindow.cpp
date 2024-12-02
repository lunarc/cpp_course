#include "mainwindow.h"

#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), m_lineEdit(nullptr)
{
    // Set the window title
    setWindowTitle("My First Qt Application");
    setGeometry(100, 100, 400, 300);

    // Create a text edit control

    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setGeometry(10, 10, 150, 24);

    // Create a button

    auto button = new QPushButton("Click Me", this);
    button->setGeometry(10, 40, 150, 30);

    // Connect the button click signal to the onButtonClicked slot

    connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
}

void MainWindow::onButtonClicked()
{
    QMessageBox::information(this, "Text in edit box", m_lineEdit->text());
}
