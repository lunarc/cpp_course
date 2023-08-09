#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJSEngine>

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

void MainWindow::modify_expression(const QString c)
{
    ui->expression_edit->setText(ui->expression_edit->text()+c);
}

void MainWindow::on_equal_button_clicked()
{
    QJSEngine engine;
    QJSValue value = engine.evaluate(ui->expression_edit->text());
    ui->result_edit->setText(value.toString());
}

void MainWindow::on_one_button_clicked()
{
    modify_expression("1");
}

void MainWindow::on_two_button_clicked()
{
    modify_expression("2");
}

void MainWindow::on_three_button_clicked()
{
    modify_expression("3");
}

void MainWindow::on_four_button_clicked()
{
    modify_expression("4");
}

void MainWindow::on_five_button_clicked()
{
    modify_expression("5");
}

void MainWindow::on_six_button_clicked()
{
    modify_expression("6");
}

void MainWindow::on_seven_button_clicked()
{
    modify_expression("7");
}

void MainWindow::on_eight_button_clicked()
{
    modify_expression("8");
}

void MainWindow::on_nine_button_clicked()
{
    modify_expression("9");
}

void MainWindow::on_zero_button_clicked()
{
    modify_expression("0");
}

void MainWindow::on_clear_button_clicked()
{
    ui->expression_edit->setText("");
    ui->result_edit->setText("");
}

void MainWindow::on_decimal_button_clicked()
{
    modify_expression(".");
}

void MainWindow::on_plus_button_clicked()
{
    modify_expression("+");
}

void MainWindow::on_minus_button_clicked()
{
    modify_expression("-");
}

void MainWindow::on_multiply_button_clicked()
{
    modify_expression("*");
}

void MainWindow::on_divide_button_clicked()
{
    modify_expression("/");
}


