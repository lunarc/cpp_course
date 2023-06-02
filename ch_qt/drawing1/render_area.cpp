#include "render_area.h"

#include <QPainter>

float rnd()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float randint(float start, float end)
{
    auto d = end - start;
    return start + d * rnd();
}

int randint(int start, int end)
{
    return int((randint(float(start), float(end))));
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
        auto r = rnd() * 150;
        auto w = rnd() * 150;
        auto h = rnd() * 150;

        if (rnd() < 0.5)
        {
            auto ellipse = DrawingKit::Ellipse::create();
            ellipse->setSize(r, r);
            ellipse->setPos(rnd() * 400.0, rnd() * 400.0);
            ellipse->setFillColor(randint(0, 255), randint(0, 255), randint(0, 255), randint(0, 255));
            m_shapes->add(ellipse);
        }
        else
        {
            auto rect = DrawingKit::Rectangle::create();
            rect->setSize(w, h);
            rect->setPos(rnd() * 400.0, rnd() * 400.0);
            rect->setFillColor(randint(0, 255), randint(0, 255), randint(0, 255), randint(0, 255));
            m_shapes->add(rect);
        }
    }
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    m_shapes->draw(painter);
}
