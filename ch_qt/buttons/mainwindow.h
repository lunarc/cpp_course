#pragma once

#include <QLineEdit>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

public slots:
    void onCalcClicked();
    void onClearClicked();

private:
    QLineEdit *m_expressionEdit;
    QLineEdit *m_resultEdit;
};
