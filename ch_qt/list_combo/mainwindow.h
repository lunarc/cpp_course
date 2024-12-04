#pragma once

#include <QCheckBox>
#include <QPushButton>
#include <QRadioButton>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

public slots:
    void onRadioButton1Toggled(bool checked);
    void onRadioButton2Toggled(bool checked);
    void onCheckBoxToggled(bool checked);
    void onCheckButtonClicked();
    void onChangeRadioButtonClicked();

private:
    QRadioButton *m_radioButton1;
    QRadioButton *m_radioButton2;
    QCheckBox *m_checkBox;
    QPushButton *m_checkButton;
    QPushButton *m_changeRadioButton;
};
