#include "mainwindow.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "exprtk.hpp"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), m_button1(nullptr), m_button2(nullptr), m_button3(nullptr)
{
    // Set the window title
    setWindowTitle("Buttons");
    setGeometry(100, 100, 400, 150);

    m_button1 = new QPushButton("Button1", this);
    m_button2 = new QPushButton("Button2", this);
    m_button3 = new QPushButton("Button3", this);

    auto layout = new QHBoxLayout(this);

    layout->addWidget(m_button1);
    layout->addWidget(m_button2);
    layout->addWidget(m_button3);

    setLayout(layout);

    connect(m_button1, SIGNAL(clicked()), this, SLOT(onButton1Clicked()));
    connect(m_button2, SIGNAL(clicked()), this, SLOT(onButton2Clicked()));
    connect(m_button3, SIGNAL(clicked()), this, SLOT(onButton3Clicked()));
}

void MainWindow::onButton1Clicked()
{
    if (m_button2->isEnabled())
    {
        m_button2->setEnabled(false);
        m_button3->setEnabled(false);
    }
    else
    {
        m_button2->setEnabled(true);
        m_button3->setEnabled(true);
    }
}

void MainWindow::onButton2Clicked()
{
    if (m_button3->isVisible())
        m_button3->setVisible(false);
    else
        m_button3->setVisible(true);
}

void MainWindow::onButton3Clicked()
{
    QMessageBox::information(this, "Button3", "Button3 clicked");
}
