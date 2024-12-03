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

    m_checkButton = new QPushButton("Check Button", this);
    m_changeRadioButton = new QPushButton("Change Radio Button", this);

    auto layout = new QHBoxLayout(this);

    auto buttonLayout = new QVBoxLayout(this);

    buttonLayout->addWidget(m_checkButton);
    buttonLayout->addWidget(m_changeRadioButton);

    auto radioChecklayout = new QVBoxLayout(this);

    radioChecklayout->addWidget(m_radioButton1);
    radioChecklayout->addWidget(m_radioButton2);
    radioChecklayout->addWidget(m_checkBox);

    layout->addLayout(radioChecklayout);
    layout->addLayout(buttonLayout);

    setLayout(layout);

    // Connect the signals

    connect(m_radioButton1, &QRadioButton::toggled, this, &MainWindow::onRadioButton1Toggled);
    connect(m_radioButton2, &QRadioButton::toggled, this, &MainWindow::onRadioButton2Toggled);
    connect(m_checkBox, &QCheckBox::toggled, this, &MainWindow::onCheckBoxToggled);
    connect(m_checkButton, &QPushButton::clicked, this, &MainWindow::onCheckButtonClicked);
    connect(m_changeRadioButton, &QPushButton::clicked, this, &MainWindow::onChangeRadioButtonClicked);
}

void MainWindow::onRadioButton1Toggled(bool checked)
{
    if (checked)
    {
        QMessageBox::information(this, "Option 1", "Option 1 is selected");
    }
}

void MainWindow::onRadioButton2Toggled(bool checked)
{
    if (checked)
    {
        QMessageBox::information(this, "Option 2", "Option 2 is selected");
    }
}

void MainWindow::onCheckBoxToggled(bool checked)
{
    if (checked)
    {
        QMessageBox::information(this, "Check 1", "Check 1 is selected");
    }
}

void MainWindow::onCheckButtonClicked()
{
    QMessageBox::information(this, "Check Button", "Check button clicked");
}

void MainWindow::onChangeRadioButtonClicked()
{
    if (m_radioButton1->isChecked())
    {
        m_radioButton2->setChecked(true);
    }
    else
    {
        m_radioButton1->setChecked(true);
    }
}
