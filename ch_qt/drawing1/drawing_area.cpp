#include "drawing_area.h"

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

DrawingArea::DrawingArea(QWidget* parent)
    : QWidget { parent }
    , m_firstTime { true }
{
    qDebug() << "constructor";

    m_shapes = DrawingKit::Group::create();
}

void DrawingArea::paintEvent(QPaintEvent* event)
{
    this->onDraw();
}

void DrawingArea::resizeEvent(QResizeEvent* event)
{
    qDebug() << "resizeEvent";
    QWidget::resizeEvent(event);

    if (m_firstTime)
    {
        this->onSetup();
        m_firstTime = false;
    }

    this->onResize();
}

void DrawingArea::onSetup()
{
    for (auto i = 0; i < 100; i++)
    {
        auto r = randfloat(50.0, 150.0);
        auto w = randfloat(50.0, 150.0);
        auto h = randfloat(50.0, 150.0);

        if (rnd() < 0.5)
        {
            auto ellipse = DrawingKit::Ellipse::create();
            ellipse->setSize(r, r);
            ellipse->setPos(rnd() * this->width(), rnd() * this->height());
            ellipse->setFillColor(randint(0, 255), randint(0, 255), randint(0, 255), randint(0, 255));
            m_shapes->add(ellipse);
        }
        else
        {
            auto rect = DrawingKit::Rectangle::create();
            rect->setSize(w, h);
            rect->setPos(rnd() * this->width(), rnd() * this->height());
            rect->setFillColor(randint(0, 255), randint(0, 255), randint(0, 255), randint(0, 255));
            m_shapes->add(rect);
        }
    }
}

void DrawingArea::onDraw()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    m_shapes->draw(painter);
}

void DrawingArea::onResize()
{
}
