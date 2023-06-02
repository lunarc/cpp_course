#include "render_area.h"

#include <QPainter>

float rnd()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float randfloat(float start, float end)
{
    auto d = end - start;
    return start + d * rnd();
}

int randint(int start, int end)
{
    return int((randfloat(float(start), float(end))));
}

RenderArea::RenderArea(QWidget *parent) : QWidget{parent}
{
    m_shapes = DrawingKit::Group::create();

    for (auto i = 0; i < 100; i++)
    {
        auto r = randfloat(50.0, 150.0);
        auto w = randfloat(50.0, 150.0);
        auto h = randfloat(50.0, 150.0);

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

void RenderArea::resizeEvent(QResizeEvent *event)
{
    this->resizeEvent(event);

}
