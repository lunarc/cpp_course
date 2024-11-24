#include "mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QFileDialog>
#include <QLabel>
#include <QMenuBar>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QStatusBar>
#include <QStyle>
#include <QTextEdit>
#include <QToolbar>
#include <QVBoxLayout>
#include <QVector>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_textEdit(nullptr)
    , m_fileName("")
    , m_wordWrapLabel(nullptr)
    , m_zoomLabel(nullptr)
{
    // Set the window title

    setWindowTitle("Text editor");
    setGeometry(100, 100, 800, 600);

    QFile toolbarStyleFile(":/styles/editor_app_toolbar.qss");
    toolbarStyleFile.open(QFile::ReadOnly);
    QString toolbarStyleSheet = QLatin1String(toolbarStyleFile.readAll());
    setStyleSheet(toolbarStyleSheet);

    QFile menuStyleFile(":/styles/editor_app_menus.qss");
    menuStyleFile.open(QFile::ReadOnly);
    QString menuStyleSheet = QLatin1String(menuStyleFile.readAll());

    // Create a central widget

    auto centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create a layout

    auto layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);

    // Set the layout

    centralWidget->setLayout(layout);

    // Text browser component initialization

    m_textEdit = new QTextEdit(centralWidget);
    m_textEdit->setFrameStyle(QFrame::StyledPanel);
    m_textEdit->setFont(QFont("Cascadia Code", 11));
    m_textEdit->setPlainText("");
    m_textEdit->setReadOnly(false);
    m_textEdit->setStyleSheet("border-bottom-color: rgb(255, 255, 255);");
    layout->addWidget(m_textEdit);

    // File menu

    QApplication::setAttribute(Qt::AA_DontShowIconsInMenus, false);

    auto fileMenu = this->menuBar()->addMenu(tr("File"));
    fileMenu->setStyleSheet(menuStyleSheet);

    auto newAction = new QAction(QIcon(":/icons/DocumentAdd.svg"), tr("New"), this);
    newAction->setShortcut(QKeySequence::New);
    connect(newAction, &QAction::triggered, this, &MainWindow::onNewDocument);
    fileMenu->addAction(newAction);

    auto openAction = new QAction(QIcon(":/icons/FolderOpen.svg"), tr("Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    // openAction->setIcon(this->style()->standardIcon(QStyle::SP_DirOpenIcon));
    connect(openAction, &QAction::triggered, this, &MainWindow::onOpenDocument);
    fileMenu->addAction(openAction);

    auto saveAction = new QAction(QIcon(":/icons/Save.svg"), tr("Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &MainWindow::onSaveDocument);
    fileMenu->addAction(saveAction);

    auto saveAsAction = new QAction(QIcon(":/icons/Save.svg"), tr("Save As"), this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::onSaveAsDocument);
    fileMenu->addAction(saveAsAction);

    fileMenu->addSeparator();

    auto exitAction = new QAction(tr("Exit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExit);
    fileMenu->addAction(exitAction);

    // Edit menu

    auto editMenu = this->menuBar()->addMenu(tr("Edit"));
    editMenu->setStyleSheet(menuStyleSheet);

    auto undoAction = new QAction(QIcon(":/icons/ArrowUndo.svg"), tr("Undo"), this);
    undoAction->setShortcut(QKeySequence::Undo);
    connect(undoAction, &QAction::triggered, this, &MainWindow::onUndo);
    editMenu->addAction(undoAction);

    editMenu->addSeparator();

    auto cutAction = new QAction(QIcon(":/icons/Cut.svg"), tr("Cut"), this);
    cutAction->setShortcut(QKeySequence::Cut);
    connect(cutAction, &QAction::triggered, this, &MainWindow::onCut);
    editMenu->addAction(cutAction);

    auto copyAction = new QAction(QIcon(":/icons/Copy.svg"), tr("Copy"), this);
    copyAction->setShortcut(QKeySequence::Copy);
    connect(copyAction, &QAction::triggered, this, &MainWindow::onCopy);
    editMenu->addAction(copyAction);

    auto pasteAction = new QAction(QIcon(":/icons/ClipboardPaste.svg"), tr("Paste"), this);
    pasteAction->setShortcut(QKeySequence::Paste);
    connect(pasteAction, &QAction::triggered, this, &MainWindow::onPaste);
    editMenu->addAction(pasteAction);

    // View menu

    auto viewMenu = this->menuBar()->addMenu(tr("View"));
    viewMenu->setStyleSheet(menuStyleSheet);

    auto zoomInAction = new QAction(QIcon(":/icons/ZoomIn.svg"), tr("Zoom In"), this);
    connect(zoomInAction, &QAction::triggered, this, &MainWindow::onZoomIn);
    viewMenu->addAction(zoomInAction);

    auto zoomOutAction = new QAction(QIcon(":/icons/ZoomOut.svg"), tr("Zoom Out"), this);
    connect(zoomOutAction, &QAction::triggered, this, &MainWindow::onZoomOut);
    viewMenu->addAction(zoomOutAction);

    m_wordWrapAction = new QAction(QIcon(":/icons/TextWrap.svg"), tr("Word Wrap"), this);
    m_wordWrapAction->setCheckable(true);

    if (m_textEdit->wordWrapMode() == QTextOption::WrapAtWordBoundaryOrAnywhere)
        m_wordWrapAction->setChecked(true);
    else
        m_wordWrapAction->setChecked(false);

    connect(m_wordWrapAction, &QAction::triggered, this, &MainWindow::onWordWrap);
    viewMenu->addAction(m_wordWrapAction);

    m_fullScreenAction = new QAction(QIcon(":/icons/FullScreenMaximize.svg"), tr("Full Screen"), this);
    m_fullScreenAction->setShortcut(QKeySequence::FullScreen);
    m_fullScreenAction->setCheckable(true);
    connect(m_fullScreenAction, &QAction::triggered, this, &MainWindow::onFullScreen);
    viewMenu->addAction(m_fullScreenAction);

    // Help menu

    auto helpMenu = this->menuBar()->addMenu(tr("Help"));
    helpMenu->setStyleSheet(menuStyleSheet);

    auto aboutAction = new QAction(tr("About"), this);
    helpMenu->addAction(aboutAction);

    // Toolbars

    auto fileToolBar = this->addToolBar(tr("File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    auto editToolBar = this->addToolBar(tr("Edit"));
    editToolBar->addAction(undoAction);
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);

    auto viewToolBar = this->addToolBar(tr("View"));
    viewToolBar->addAction(zoomInAction);
    viewToolBar->addAction(zoomOutAction);
    viewToolBar->addAction(m_wordWrapAction);
    viewToolBar->addAction(m_fullScreenAction);

    // Status bar initialization

    auto statusBar = new QStatusBar(this);
    m_wordWrapLabel = new QLabel("Ready", this);
    m_zoomLabel = new QLabel("100%", this);
    statusBar->addWidget(m_wordWrapLabel);
    statusBar->addWidget(m_zoomLabel);
    statusBar->setContentsMargins(5, 2, 5, 5);
    setStatusBar(statusBar);

    updateStatus();
    updateTitle();
}

MainWindow::~MainWindow()
{
}

void MainWindow::onNewDocument()
{
    m_fileName = "";
    m_textEdit->clear();
    updateTitle();
    updateStatus();
}

void MainWindow::onOpenDocument()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("All files (*.*);;Text Files (*.txt);;C++ Files (*.cpp *.h)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;

    m_fileName = fileName;
    updateStatus();
    updateTitle();

    m_textEdit->clear();
    QTextStream in(&file);
    m_textEdit->document()->setPlainText(in.readAll());
}

void MainWindow::onSaveDocument()
{
    if (m_fileName.isEmpty())
    {
        onSaveAsDocument();
        return;
    }

    QFile file(m_fileName);
    if (!file.open(QIODevice::WriteOnly))
        return;

    QTextStream out(&file);
    out << m_textEdit->document()->toPlainText();
}

void MainWindow::onSaveAsDocument()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));
    if (fileName.isEmpty())
        return;

    m_fileName = fileName;
    updateStatus();
    updateTitle();
    onSaveDocument();
}

void MainWindow::onExit()
{
    this->close();
}

void MainWindow::onUndo()
{
    m_textEdit->undo();
}

void MainWindow::onCopy()
{
    m_textEdit->copy();
}

void MainWindow::onCut()
{
    m_textEdit->cut();
}

void MainWindow::onPaste()
{
    m_textEdit->paste();
}

void MainWindow::onZoomIn()
{
    m_textEdit->zoomIn();
    updateStatus();
}

void MainWindow::onZoomOut()
{
    m_textEdit->zoomOut();
    updateStatus();
}

void MainWindow::onWordWrap()
{
    if (m_wordWrapAction->isChecked())
        m_wordWrapAction->setChecked(true);
    else
        m_wordWrapAction->setChecked(false);

    if (m_wordWrapAction->isChecked())
        m_textEdit->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    else
        m_textEdit->setWordWrapMode(QTextOption::NoWrap);

    updateStatus();
}

void MainWindow::onFullScreen()
{
    if (m_fullScreenAction->isChecked())
        m_fullScreenAction->setChecked(true);
    else
        m_fullScreenAction->setChecked(false);

    if (m_fullScreenAction->isChecked())
        showFullScreen();
    else
        showNormal();
}

QString MainWindow::shortFilename(const QString& fileName)
{
    return QFileInfo(fileName).fileName();
}

void MainWindow::updateStatus()
{
    if (m_wordWrapAction->isChecked())
        m_wordWrapLabel->setText("Word Wrap: On ");
    else
        m_wordWrapLabel->setText("Word Wrap: Off ");

    m_zoomLabel->setText(QString::number(100 * m_textEdit->font().pointSize() / 11) + "% ");
}

void MainWindow::updateTitle()
{
    QString title = "Text editor";
    if (!m_fileName.isEmpty())
        title += " - " + shortFilename(m_fileName);
    setWindowTitle(title);
}
