#pragma once

#include <QWidget>
#include <QBrush>
#include <QPen>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

signals:

private:
    QBrush m_brush;
    QPen m_pen;

};
