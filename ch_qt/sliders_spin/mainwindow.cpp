#include "mainwindow.h"

#include <QButtonGroup>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "exprtk.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), m_dateTimeEdit{nullptr}, m_dial{nullptr},
      m_doubleSpinBox{nullptr}, m_slider{nullptr}, m_spinBox{nullptr}
{
    // Set the window title

    setWindowTitle("Sliders and more");
    setGeometry(100, 100, 400, 150);

    // Create the buttons

    m_dateTimeEdit = new QDateTimeEdit(this);

    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setRange(0, 100);
    m_slider->setValue(0);

    m_spinBox = new QSpinBox(this);
    m_spinBox->setRange(0, 100);
    m_spinBox->setValue(0);

    m_doubleSpinBox = new QDoubleSpinBox(this);
    m_doubleSpinBox->setRange(0, 100);
    m_doubleSpinBox->setValue(0);

    m_dial = new QDial(this);
    m_dial->setRange(0, 100);
    m_dial->setValue(0);

    auto layout = new QVBoxLayout(this);

    layout->addWidget(m_dateTimeEdit);
    layout->addWidget(m_slider);
    layout->addWidget(m_spinBox);
    layout->addWidget(m_doubleSpinBox);
    layout->addWidget(m_dial);

    setLayout(layout);

    // Connect the signals and slots

    connect(m_slider, &QSlider::valueChanged, this, &MainWindow::onSliderValueChanged);
    connect(m_spinBox, static_cast< void (QSpinBox::*)(int) >(&QSpinBox::valueChanged), this,
            &MainWindow::onSpinBoxValueChanged);
    connect(m_doubleSpinBox, static_cast< void (QDoubleSpinBox::*)(double) >(&QDoubleSpinBox::valueChanged), this,
            &MainWindow::onDoubleSpinBoxValueChanged);
    connect(m_dial, &QDial::valueChanged, this, &MainWindow::onDialValueChanged);
}

void MainWindow::onSliderValueChanged(int value)
{
    m_spinBox->setValue(value);
    m_doubleSpinBox->setValue(value);
    m_dial->setValue(value);
}

void MainWindow::onSpinBoxValueChanged(int value)
{
    m_slider->setValue(value);
    m_doubleSpinBox->setValue(value);
    m_dial->setValue(value);
}

void MainWindow::onDoubleSpinBoxValueChanged(double value)
{
    m_slider->setValue(value);
    m_spinBox->setValue(value);
    m_dial->setValue(value);
}

void MainWindow::onDialValueChanged(int value)
{
    m_slider->setValue(value);
    m_spinBox->setValue(value);
    m_doubleSpinBox->setValue(value);
}

void MainWindow::onDateTimeEditValueChanged(const QDateTime &dateTime)
{
    // QMessageBox::information(this, "Date and time", dateTime.toString());
}
