// customtitlebar.cpp
#include "custom_title_bar.h"
#include <QApplication>
#include <QMouseEvent>

CustomTitleBar::CustomTitleBar(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
    setFixedHeight(32);
    setStyleSheet("background-color: #f0f0f0;");
}

void CustomTitleBar::setupUI()
{
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 0, 10, 0);
    layout->setSpacing(0);

    // Window icon (optional)
    auto icon = new QLabel(this);
    icon->setPixmap(QPixmap(":/icon.png").scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    layout->addWidget(icon);
    layout->addSpacing(10);

    // Title
    titleLabel = new QLabel("Window Title", this);
    layout->addWidget(titleLabel);
    layout->addStretch();

    createButtons();
}

void CustomTitleBar::createButtons()
{
    // Create window control buttons
    minimizeButton = new QPushButton("−", this);
    maximizeButton = new QPushButton("□", this);
    closeButton = new QPushButton("×", this);

    minimizeButton->setFixedSize(46, 32);
    maximizeButton->setFixedSize(46, 32);
    closeButton->setFixedSize(46, 32);

    setButtonStyle();

    auto layout = qobject_cast<QHBoxLayout*>(this->layout());
    layout->addWidget(minimizeButton);
    layout->addWidget(maximizeButton);
    layout->addWidget(closeButton);

    connect(minimizeButton, &QPushButton::clicked, this, &CustomTitleBar::onMinimizeClicked);
    connect(maximizeButton, &QPushButton::clicked, this, &CustomTitleBar::onMaximizeClicked);
    connect(closeButton, &QPushButton::clicked, this, &CustomTitleBar::onCloseClicked);
}

void CustomTitleBar::setButtonStyle()
{
    QString baseStyle = "QPushButton { border: none; background: transparent; }"
                        "QPushButton:hover { background: %1; }";

    minimizeButton->setStyleSheet(baseStyle.arg("#e5e5e5"));
    maximizeButton->setStyleSheet(baseStyle.arg("#e5e5e5"));
    closeButton->setStyleSheet(
        baseStyle.arg("#e81123") + "QPushButton:hover { color: white; }");
}

void CustomTitleBar::setTitle(const QString& title)
{
    titleLabel->setText(title);
}

void CustomTitleBar::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragPosition = event->globalPosition().toPoint() - parentWidget()->frameGeometry().topLeft();
        event->accept();
    }
}

void CustomTitleBar::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        parentWidget()->move(event->globalPosition().toPoint() - dragPosition);
        event->accept();
    }
}

void CustomTitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        onMaximizeClicked();
    }
}

void CustomTitleBar::onMinimizeClicked()
{
    parentWidget()->showMinimized();
}

void CustomTitleBar::onMaximizeClicked()
{
    if (isMaximized)
    {
        parentWidget()->showNormal();
        maximizeButton->setText("□");
    }
    else
    {
        parentWidget()->showMaximized();
        maximizeButton->setText("❐");
    }
    isMaximized = !isMaximized;
}

void CustomTitleBar::onCloseClicked()
{
    parentWidget()->close();
}
