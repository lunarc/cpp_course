#include "mainwindow.h"

#include <QButtonGroup>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), m_listWidget(nullptr), m_lineEdit(nullptr)
{
    // Set the window title
    setWindowTitle("List boxes and combos");
    setGeometry(100, 100, 400, 150);

    m_listWidget = new QListWidget(this);
    m_lineEdit = new QLineEdit(this);
    m_comboBox = new QComboBox(this);

    auto addButton = new QPushButton("Add", this);
    auto removeButton = new QPushButton("Remove", this);
    auto clearButton = new QPushButton("Clear", this);

    auto mainLayout = new QHBoxLayout(this);
    auto leftLayout = new QVBoxLayout(this);
    auto rightLayout = new QVBoxLayout(this);

    leftLayout->addWidget(m_lineEdit);
    leftLayout->addWidget(m_listWidget);
    leftLayout->addWidget(m_comboBox);

    rightLayout->addWidget(addButton);
    rightLayout->addWidget(removeButton);
    rightLayout->addWidget(clearButton);
    rightLayout->addStretch();

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    setLayout(mainLayout);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddButtonClicked);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveButtonClicked);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearButtonClicked);
    connect(m_listWidget, &QListWidget::itemSelectionChanged, this, &MainWindow::onItemSelectionChanged);
    connect(m_comboBox, &QComboBox::currentTextChanged, this, &MainWindow::onComboCurrentTextChanged);
}

void MainWindow::onAddButtonClicked()
{
    // Get the text from the line edit

    QString text = m_lineEdit->text();

    // Check if the text is empty

    if (text.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please enter some text");
        return;
    }

    // Add the text to the list widget

    m_listWidget->addItem(text);
    m_comboBox->addItem(text);
}

void MainWindow::onRemoveButtonClicked()
{
    // Get the selected item

    auto item = m_listWidget->currentItem();

    // Check if an item is selected

    if (!item)
    {
        QMessageBox::warning(this, "Error", "Please select an item to remove");
        return;
    }

    delete item;
}

void MainWindow::onClearButtonClicked()
{
    // Clear all items from the list widget

    m_listWidget->clear();
    m_comboBox->clear();
}

void MainWindow::onItemSelectionChanged()
{
    // Get the selected item

    auto item = m_listWidget->currentItem();

    // Check if an item is selected

    if (!item)
    {
        return;
    }

    // Get the text of the selected item

    QString text = item->text();

    // Set the text of the line edit

    m_lineEdit->setText(text);
}

void MainWindow::onComboCurrentTextChanged()
{
    // Get the current text of the combo box

    QString text = m_comboBox->currentText();

    // Set the text of the line edit

    m_lineEdit->setText(text);
}
