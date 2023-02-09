#include "render_area.h"

#include <QPainter>

RenderArea::RenderArea(QWidget *parent)
    : QWidget{parent}
{
    m_pen.setColor(Qt::red);
    m_pen.setWidth(2);
    m_brush.setColor(Qt::green);
    m_brush.setStyle(Qt::SolidPattern);
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(m_pen);
    painter.setBrush(m_brush);

    painter.drawLine(this->rect().bottomLeft(), this->rect().topRight());
    painter.drawLine(this->rect().topLeft(), this->rect().bottomRight());
    painter.drawEllipse(this->width()/2.0-20, this->height()/2.0-20, 40, 40);
}
