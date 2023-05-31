#include "render_area.h"

#include <QPainter>

float rnd()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

RenderArea::RenderArea(QWidget *parent) : QWidget{parent}
{
    m_pen.setColor(Qt::red);
    m_pen.setWidth(2);
    m_brush.setColor(Qt::green);
    m_brush.setStyle(Qt::SolidPattern);

    m_shapes = DrawingKit::Group::create();

    for (auto i = 0; i < 100; i++)
    {
        auto ellipse = DrawingKit::Ellipse::create();
        auto r = rnd() * 150;
        ellipse->setSize(r, r);
        ellipse->setPos(rnd() * 400.0, rnd() * 400.0);
        ellipse->setFillColor(255, 255, 0);

        m_shapes->add(ellipse);
    }
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    m_shapes->draw(painter);
}
