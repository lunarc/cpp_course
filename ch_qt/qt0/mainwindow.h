#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget*parent = 0);
    ~MainWindow();

public slots:
	void on_button_clicked();

private:
};

#endif // MAINWINDOW_H
