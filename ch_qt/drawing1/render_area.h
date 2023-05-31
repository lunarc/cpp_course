#pragma once

#include <QBrush>
#include <QPen>
#include <QWidget>

#include "drawing_kit.h"

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

    DrawingKit::GroupPtr m_shapes;
};
