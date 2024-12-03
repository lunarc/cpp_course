#pragma once

#include <QCheckBox>
#include <QRadioButton>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

public slots:

private:
    QRadioButton *m_radioButton1;
    QRadioButton *m_radioButton2;
    QCheckBox *m_checkBox;
};
