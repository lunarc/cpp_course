#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox->addItem("A");
    ui->comboBox->addItem("B");
    ui->comboBox->addItem("C");
    ui->comboBox->addItem("D");
    ui->comboBox->addItem("E");

    ui->listWidget->addItem("Windows");
    ui->listWidget->addItem("Mac");
    ui->listWidget->addItem("Linux");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_extraAllCheck_toggled(bool checked)
{
    if (checked == true)
        QMessageBox::information(this, "Message", "Extra allt");
    else
        QMessageBox::information(this, "Message", "Nothing");
}


void MainWindow::on_alt1Radio_clicked()
{
    QMessageBox::information(this, "Message", "Alternative 1");
}

void MainWindow::on_alt2Radio_clicked()
{
    QMessageBox::information(this, "Message", "Alternative 2");
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QMessageBox::information(this, "Message", arg1);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    QMessageBox::information(this, "Message", QString::number(index));
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    QMessageBox::information(this, "Message", QString::number(currentRow));
}

void MainWindow::on_listWidget_currentTextChanged(const QString &currentText)
{
    QMessageBox::information(this, "Message", currentText);
}

void MainWindow::on_upperCaseButton_clicked()
{
    QMessageBox::information(this, "Message", ui->lineEdit->text().toUpper());
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->valueEdit->setText(QString::number(value));
}
