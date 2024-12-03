#pragma once

#include <QPushButton>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

public slots:
    void onButton1Clicked();
    void onButton2Clicked();
    void onButton3Clicked();

private:
    QPushButton *m_button1;
    QPushButton *m_button2;
    QPushButton *m_button3;
};
