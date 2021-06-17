#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void modify_expression(const QString c);

private slots:
    void on_equal_button_clicked();
    void on_one_button_clicked();
    void on_two_button_clicked();
    void on_three_button_clicked();
    void on_four_button_clicked();
    void on_five_button_clicked();
    void on_six_button_clicked();
    void on_seven_button_clicked();
    void on_eight_button_clicked();
    void on_nine_button_clicked();
    void on_zero_button_clicked();
    void on_clear_button_clicked();
    void on_decimal_button_clicked();
    void on_plus_button_clicked();
    void on_minus_button_clicked();
    void on_multiply_button_clicked();
    void on_divide_button_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
