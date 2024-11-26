#pragma once

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class CustomTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit CustomTitleBar(QWidget* parent = nullptr);
    void setTitle(const QString& title);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    QLabel* titleLabel;
    QPushButton* minimizeButton;
    QPushButton* maximizeButton;
    QPushButton* closeButton;
    QPoint dragPosition;
    bool isMaximized = false;

    void setupUI();
    void createButtons();
    void setButtonStyle();

private slots:
    void onMinimizeClicked();
    void onMaximizeClicked();
    void onCloseClicked();
};
