#include "beam_view.h"
#include "qevent.h"

#include <QPainter>

#include <cmath>

BeamView::BeamView(QWidget *parent)
    : QWidget{parent},
      m_margins{ 0.2 },
      m_scaleFactor{ 1.0 },
      m_loadScaleFactor{ 1.0 },
      m_selectedBeam{-1},
      m_overBeam{-1},
      m_prevOverBeam{-1}
{
    m_pen.setColor(Qt::black);
    m_pen.setWidth(1);
    m_brush.setColor(Qt::white);
    m_brush.setStyle(Qt::SolidPattern);

    m_selectedBeamPen.setColor(Qt::red);
    m_selectedBeamPen.setWidth(1);

    m_overBeamPen.setColor(Qt::gray);

    m_selectedBeam = 0;

    this->setMouseTracking(true);
}

void BeamView::setBeamModel(BeamModelPtr model)
{
    m_beamModel = model;
}

int BeamView::selectedBeam()
{
    return m_selectedBeam;
}

void BeamView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(m_pen);
    painter.setBrush(m_brush);

    painter.drawRect(0, 0, this->width(), this->height());

    //painter.drawLine(this->rect().bottomLeft(), this->rect().topRight());
    //painter.drawLine(this->rect().topLeft(), this->rect().bottomRight());
    //painter.drawEllipse(this->width()/2.0-20, this->height()/2.0-20, 40, 40);

    auto totalLength = m_beamModel->length();

    m_scaleFactor = this->width()*(1.0-m_margins)/totalLength;
    m_loadScaleFactor = this->height()*0.1/m_beamModel->maxLoad();

    drawLoads(painter);
    drawDimensions(painter);
    drawSupports(painter);
    drawBeams(painter);
}

void BeamView::mouseMoveEvent(QMouseEvent *event)
{
    m_overBeam = m_beamModel->beam_pos_from_x(to_x(event->pos().x())+m_beamModel->length()/2.0);
    if (m_prevOverBeam!=m_overBeam)
        this->repaint();
    m_prevOverBeam = m_overBeam;
}

void BeamView::mousePressEvent(QMouseEvent *event)
{
    auto pressed_beam = m_beamModel->beam_pos_from_x(to_x(event->pos().x())+m_beamModel->length()/2.0);
    if (pressed_beam!=-1)
    {
        m_selectedBeam = pressed_beam;
        this->repaint();
        emit beamSelected(m_selectedBeam);
    }
}

int BeamView::to_sx(double x)
{
    return this->width()/2.0 + std::round(x*m_scaleFactor);
}

int BeamView::to_sy(double y)
{
    return this->height()/2.0 - std::round(y*m_scaleFactor);
}

double BeamView::to_x(int x)
{
    return (x-this->width()/2)/m_scaleFactor;
}

double BeamView::to_y(int x)
{
    return (x-this->height()/2)/m_scaleFactor;
}

void BeamView::drawBeams(QPainter &painter)
{
    auto x = -m_beamModel->length()/2.0;
    auto y = 0.0;

    auto i = 0;

    for (auto& beam : m_beamModel->beams())
    {
        if (m_selectedBeam == i)
            painter.setPen(m_selectedBeamPen);
        else if (m_overBeam == i)
            painter.setPen(m_overBeamPen);
        else
            painter.setPen(m_pen);

        painter.drawLine(to_sx(x), to_sy(y), to_sx(x + beam->l()), to_sy(y));
        x += beam->l();

        i++;
    }
}

void BeamView::drawSupports(QPainter &painter)
{
    auto x = -m_beamModel->length()/2.0;
    auto y = 0.0;

    for (auto& beam : m_beamModel->beams())
    {
        auto sx = to_sx(x);
        auto sy = to_sy(y);

        painter.drawEllipse(sx-5, sy, 10, 10);
        painter.drawLine(sx-10, sy+10, sx+10, sy+10);

        x += beam->l();
    }
    auto sx = to_sx(x);
    auto sy = to_sy(y);

    painter.drawEllipse(sx-5, sy, 10, 10);
    painter.drawLine(sx-10, sy+10, sx+10, sy+10);
}

void BeamView::drawLoads(QPainter &painter)
{
    auto x = -m_beamModel->length()/2.0;
    auto y = 0.0;

    for (auto& beam : m_beamModel->beams())
    {
        auto sx = to_sx(x);
        auto sy = to_sy(y);

        painter.drawRect(sx, sy-20-beam->q()*m_loadScaleFactor, beam->l()*m_scaleFactor, beam->q()*m_loadScaleFactor);

        x += beam->l();
    }
    auto sx = to_sx(x);
    auto sy = to_sy(y);

    painter.drawEllipse(sx-5, sy, 10, 10);
}

void BeamView::drawDimensions(QPainter &painter)
{

}
