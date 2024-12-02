#pragma once

#include <QLineEdit>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

public slots:
    void onButtonClicked();

private:
    QLineEdit *m_lineEdit;
};
