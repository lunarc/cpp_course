#pragma once

#include <QMainWindow>
#include <QTextBrowser>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onNewDocument();

private:
    QTextBrowser* m_textBrowser{ nullptr };
};

