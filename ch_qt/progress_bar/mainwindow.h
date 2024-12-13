#pragma once

#include <QProgressBar>
#include <QTimer>
#include <QWidget>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

public slots:
    void onForwardButtonClicked();
    void onBackwardButtonClicked();
    void onResetButtonClicked();
    void onStartButtonClicked();
    void onStopButtonClicked();
    void onTimerTimeout();

private:
    QProgressBar *m_progressBar;
    QTimer *m_timer;
};
