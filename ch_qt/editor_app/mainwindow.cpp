#include "mainwindow.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QAction>
#include <QStatusBar>
#include <QTextBrowser>
#include <QPlainTextEdit>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Set the window title
    setWindowTitle("Hello World");
    setGeometry(100, 100, 800, 600);

    // Create a central widget
    auto centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create a layout
    auto layout = new QVBoxLayout(centralWidget);

    // Set the layout
    centralWidget->setLayout(layout);

    // Main menu
    
    auto fileMenu = this->menuBar()->addMenu(tr("File"));

    //auto font = this->menuBar()->font();
    //fileMenu->setFont(font);

    auto newAction = new QAction(tr("New"), this);
    connect(newAction, &QAction::triggered, this, &MainWindow::onNewDocument);
    fileMenu->addAction(newAction);
    auto openAction = new QAction(tr("Open"), this);
    fileMenu->addAction(openAction);
    auto saveAction = new QAction(tr("Save"), this);
    fileMenu->addAction(saveAction);
    auto saveAsAction = new QAction(tr("Save As"), this);
    fileMenu->addAction(saveAsAction);
    auto exitAction = new QAction(tr("Exit"), this);
    fileMenu->addAction(exitAction);

    auto editMenu = this->menuBar()->addMenu(tr("Edit"));

    auto cutAction = new QAction(tr("Cut"), this);
    editMenu->addAction(cutAction);
    auto copyAction = new QAction(tr("Copy"), this);
    editMenu->addAction(copyAction);
    auto pasteAction = new QAction(tr("Paste"), this);
    editMenu->addAction(pasteAction);

    auto helpMenu = this->menuBar()->addMenu(tr("Help"));

    auto aboutAction = new QAction(tr("About"), this);
    helpMenu->addAction(aboutAction);

    auto viewMenu = this->menuBar()->addMenu(tr("View"));

    auto zoomInAction = new QAction(tr("Zoom In"), this);
    viewMenu->addAction(zoomInAction);
    auto zoomOutAction = new QAction(tr("Zoom Out"), this);
    viewMenu->addAction(zoomOutAction);
    auto wordWrapAction = new QAction(tr("Word Wrap"), this);
    viewMenu->addAction(wordWrapAction);
    auto fullScreenAction = new QAction(tr("Full Screen"), this);
    viewMenu->addAction(fullScreenAction);
    auto normalScreenAction = new QAction(tr("Normal Screen"), this);
    viewMenu->addAction(normalScreenAction);

    m_textBrowser = new QTextBrowser(centralWidget);
    m_textBrowser->setFrameStyle(QFrame::StyledPanel);
    m_textBrowser->setFont(QFont("Cascadia Code", 11));
    m_textBrowser->setPlainText("Hello World");
    m_textBrowser->setReadOnly(false);
    layout->addWidget(m_textBrowser);

    auto statusBar = new QStatusBar(this);
    auto label = new QLabel("Ready", this);
    statusBar->addWidget(label);
    setStatusBar(statusBar);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onNewDocument()
{
    m_textBrowser->clear();
}
