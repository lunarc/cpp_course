#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_infoButton_clicked()
{
    QMessageBox::information(this, "Dialog", "This is an informational text");
}

void MainWindow::on_warningButton_clicked()
{
    QMessageBox::warning(this, "Dialog", "This is an warning");
}

void MainWindow::on_errorButton_clicked()
{
    QMessageBox::critical(this, "Dialog", "This is an error");
}

void MainWindow::on_yesNoButton_clicked()
{
    int answer = QMessageBox::question(this, "Dialog", "Remove", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (answer == QMessageBox::Yes)
        QMessageBox::information(this, "Dialog", "Harddrive erased");
    else
        QMessageBox::information(this, "Dialog", "No harddrive erased (only corrupted...)");
}

void MainWindow::on_openButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open file", "", "(*.py)");

    if (filename!="")
        QMessageBox::information(this, "Dialog", filename);
}

void MainWindow::on_saveButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save file", "", "(*.py)");

    if (filename!="")
        QMessageBox::information(this, "Dialog", filename);
}
