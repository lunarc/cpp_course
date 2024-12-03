#include "mainwindow.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "exprtk.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), m_checkBox(nullptr), m_radioButton1(nullptr), m_radioButton2(nullptr)
{
    // Set the window title
    setWindowTitle("Buttons");
    setGeometry(100, 100, 400, 150);

    // Create the buttons

    m_radioButton1 = new QRadioButton("Option 1", this);
    m_radioButton2 = new QRadioButton("Option 2", this);

    m_checkBox = new QCheckBox("Check 1", this);

    auto layout = new QVBoxLayout(this);

    layout->addWidget(m_radioButton1);
    layout->addWidget(m_radioButton2);
    layout->addWidget(m_checkBox);

    setLayout(layout);
}
