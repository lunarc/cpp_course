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

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), m_timer(nullptr), m_progressBar(nullptr)
{
    // Set the window title

    setWindowTitle("Progress bars");
    setGeometry(100, 100, 400, 150);

    // Create the buttons

    auto forwardButton = new QPushButton("Forward", this);
    auto backwardButton = new QPushButton("Backward", this);
    auto resetButton = new QPushButton("Reset", this);
    auto startButton = new QPushButton("Start", this);
    auto stopButton = new QPushButton("Stop", this);

    m_progressBar = new QProgressBar(this);

    auto layout = new QVBoxLayout(this);
    auto horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->addWidget(backwardButton);
    horizontalLayout->addWidget(forwardButton);
    horizontalLayout->addWidget(resetButton);
    horizontalLayout->addWidget(startButton);
    horizontalLayout->addWidget(stopButton);

    layout->addLayout(horizontalLayout);
    layout->addWidget(m_progressBar);
    layout->addStretch();

    // Create a timer

    m_timer = new QTimer(this);

    setLayout(layout);

    // Connect the signals and slots

    connect(forwardButton, &QPushButton::clicked, this, &MainWindow::onForwardButtonClicked);
    connect(backwardButton, &QPushButton::clicked, this, &MainWindow::onBackwardButtonClicked);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::onResetButtonClicked);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::onStopButtonClicked);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::onTimerTimeout);
}

void MainWindow::onForwardButtonClicked()
{
    m_progressBar->setValue(m_progressBar->value() + 10);
}

void MainWindow::onBackwardButtonClicked()
{
    m_progressBar->setValue(m_progressBar->value() - 10);
}

void MainWindow::onResetButtonClicked()
{
    m_progressBar->reset();
}

void MainWindow::onStartButtonClicked()
{
    m_progressBar->setRange(0, 100);
    m_progressBar->setValue(0);
    m_timer->start(100);
}

void MainWindow::onStopButtonClicked()
{
    m_timer->stop();
}

void MainWindow::onTimerTimeout()
{
    m_progressBar->setValue(m_progressBar->value() + 1);
}
