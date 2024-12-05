#pragma once

#include <QDateTimeEdit>
#include <QDial>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QSpinBox>
#include <QWidget>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

public slots:
    void onSliderValueChanged(int value);
    void onSpinBoxValueChanged(int value);
    void onDoubleSpinBoxValueChanged(double value);
    void onDialValueChanged(int value);
    void onDateTimeEditValueChanged(const QDateTime &dateTime);

private:
    QSlider *m_slider;
    QSpinBox *m_spinBox;
    QDoubleSpinBox *m_doubleSpinBox;
    QDial *m_dial;
    QDateTimeEdit *m_dateTimeEdit;
};
