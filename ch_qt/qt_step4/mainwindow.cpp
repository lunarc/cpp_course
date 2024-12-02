#include "mainwindow.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "exprtk.hpp"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), m_expressionEdit(nullptr), m_resultEdit(nullptr)
{
    // Set the window title
    setWindowTitle("Expression evaluator");
    setGeometry(100, 100, 400, 150);

    // Create a label

    auto labelExpression = new QLabel("Enter an expression:", this);
    auto labelResult = new QLabel("Result:", this);

    // Create a text edit control

    m_expressionEdit = new QLineEdit(this);
    m_expressionEdit->setPlaceholderText("Enter an expression");
    m_expressionEdit->setMinimumWidth(200);

    m_resultEdit = new QLineEdit(this);
    m_resultEdit->setReadOnly(true);
    m_resultEdit->setMinimumWidth(200);

    // Create a evaluate button

    auto calcButton = new QPushButton("Evaluate", this);
    auto clearButton = new QPushButton("Clear", this);

    // Create UI layout

    auto verticalLayout = new QVBoxLayout(this);

    auto expressionLayout = new QHBoxLayout(this);
    expressionLayout->addStretch();
    expressionLayout->addWidget(labelExpression);
    expressionLayout->addWidget(m_expressionEdit);

    auto resultLayout = new QHBoxLayout(this);
    resultLayout->addStretch();
    resultLayout->addWidget(labelResult);
    resultLayout->addWidget(m_resultEdit);

    auto buttonLayout = new QHBoxLayout(this);
    buttonLayout->addStretch();
    buttonLayout->addWidget(calcButton);
    buttonLayout->addWidget(clearButton);
    buttonLayout->addStretch();

    verticalLayout->addLayout(expressionLayout);
    verticalLayout->addLayout(resultLayout);
    verticalLayout->addStretch();
    verticalLayout->addLayout(buttonLayout);

    // Set the layout

    setLayout(verticalLayout);

    // Connect the button click signal to the onButtonClicked slot

    connect(calcButton, &QPushButton::clicked, this, &MainWindow::onCalcClicked);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearClicked);
}

void MainWindow::onClearClicked()
{
    // Clear the text edit controls

    m_expressionEdit->clear();
    m_resultEdit->clear();
}

void MainWindow::onCalcClicked()
{
    // Read the expression from the text edit control

    auto expressionString = m_expressionEdit->text().toStdString();

    // Evaluate the expression using the exprtk library

    exprtk::symbol_table<double> symbolTable;
    exprtk::expression<double> expression;
    exprtk::parser<double> parser;

    symbolTable.add_constants();
    expression.register_symbol_table(symbolTable);
    parser.compile(expressionString, expression);

    // Display the result in the result text edit control

    double result = expression.value();
    m_resultEdit->setText(QString::number(result));
}
