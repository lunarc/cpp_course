#include "beam_view.h"
#include "qevent.h"

#include <QApplication>
#include <QPainter>

#include <cmath>

using namespace BeamAnalysis;

BeamView::BeamView(QWidget* parent)
    : QWidget { parent }
    , m_margins { 0.2 }
    , m_scaleFactor { 1.0 }
    , m_loadScaleFactor { 1.0 }
    , m_selectedBeam { -1 }
    , m_overBeam { -1 }
    , m_prevOverBeam { -1 }
    , m_showLoads { true }
    , m_showMoments { true }
    , m_showShear { true }
    , m_showDeflections { true }
{
    m_pen.setColor(Qt::black);
    m_pen.setWidth(1);

    m_brush.setColor(Qt::white);

    m_brush.setStyle(Qt::SolidPattern);

    m_momentPen.setColor(Qt::darkRed);
    m_momentPen.setWidth(2);

    m_momentBrush.setColor(Qt::red);
    m_momentBrush.setStyle(Qt::SolidPattern);

    m_shearBrush.setColor(Qt::blue);
    m_shearBrush.setStyle(Qt::SolidPattern);

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

void BeamAnalysis::BeamView::updateDarkModeColors()
{
    if (isDarkModePalette())
        m_brush.setColor(Qt::black);
    else
        m_brush.setColor(Qt::white);

    if (isDarkModePalette())
        m_pen.setColor(Qt::white);
    else
        m_pen.setColor(Qt::black);
}

void BeamView::showMoments(bool flag)
{
    m_showMoments = flag;
}

void BeamView::showShear(bool flag)
{
    m_showShear = flag;
}

void BeamView::showDeflections(bool flag)
{
    m_showDeflections = flag;
}

void BeamView::showLoads(bool flag)
{
    m_showLoads = flag;
}

bool BeamView::showLoads()
{
    return m_showLoads;
}

bool BeamView::showShear()
{
    return m_showShear;
}

bool BeamView::showMoments()
{
    return m_showMoments;
}

bool BeamView::showDeflections()
{
    return m_showDeflections;
}

void BeamView::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    updateDarkModeColors();

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::NoPen);
    painter.setBrush(m_brush);

    painter.drawRect(0, 0, this->width(), this->height());

    painter.setPen(m_pen);

    // painter.drawLine(this->rect().bottomLeft(), this->rect().topRight());
    // painter.drawLine(this->rect().topLeft(), this->rect().bottomRight());
    // painter.drawEllipse(this->width()/2.0-20, this->height()/2.0-20, 40, 40);

    auto totalLength = m_beamModel->length();

    m_scaleFactor = this->width() * (1.0 - m_margins) / totalLength;
    m_loadScaleFactor = this->height() * 0.1 / m_beamModel->maxLoad();
    m_deflectionScaleFactor = this->height() * 0.1 / m_beamModel->maxv();

    m_MscaleFactor = this->height() * 0.1 / m_beamModel->maxM();
    m_VscaleFactor = this->height() * 0.1 / m_beamModel->maxV();

    if (m_showLoads)
        drawLoads(painter);

    drawDimensions(painter);

    if (m_showDeflections)
        drawDeflections(painter);

    if (m_showMoments)
        drawM(painter);

    if (m_showShear)
        drawV(painter);

    drawSupports(painter);
    drawBeams(painter);
}

void BeamView::mouseMoveEvent(QMouseEvent* event)
{
    m_overBeam = m_beamModel->beam_pos_from_x(to_x(event->pos().x()) + m_beamModel->length() / 2.0);
    if (m_prevOverBeam != m_overBeam)
        this->repaint();
    m_prevOverBeam = m_overBeam;
}

void BeamView::mousePressEvent(QMouseEvent* event)
{
    auto pressed_beam = m_beamModel->beam_pos_from_x(to_x(event->pos().x()) + m_beamModel->length() / 2.0);
    if (pressed_beam != -1)
    {
        m_selectedBeam = pressed_beam;
        this->repaint();
        emit beamSelected(m_selectedBeam);
    }
}

double BeamView::to_sx(double x)
{
    return this->width() / 2.0 + x * m_scaleFactor;
}

double BeamView::to_sy(double y)
{
    return this->height() / 2.0 - y * m_scaleFactor;
}

double BeamView::to_x(double x)
{
    return (x - this->width() / 2) / m_scaleFactor;
}

double BeamView::to_y(double x)
{
    return (x - this->height() / 2) / m_scaleFactor;
}

void BeamView::drawLineWithArrow(QPainter& painter, int x0, int y0, int x1, int y1)
{
    qreal arrowSize = 10; // size of head

    QLineF line(QPointF(x1, y1), QPointF(x0, y0));

    double angle = std::atan2(-line.dy(), line.dx());
    QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize, cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize, cos(angle + M_PI - M_PI / 3) * arrowSize);

    QPolygonF arrowHead;
    arrowHead.clear();
    arrowHead << line.p1() << arrowP1 << arrowP2;
    painter.drawLine(line);
    painter.drawPolygon(arrowHead);
}

void BeamView::drawBeams(QPainter& painter)
{
    auto x = -m_beamModel->length() / 2.0;
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

void BeamView::drawSupports(QPainter& painter)
{
    auto x = -m_beamModel->length() / 2.0;
    auto y = 0.0;

    for (auto& beam : m_beamModel->beams())
    {
        auto sx = to_sx(x);
        auto sy = to_sy(y);

        painter.drawEllipse(sx - 5, sy, 10, 10);
        painter.drawLine(sx - 10, sy + 10, sx + 10, sy + 10);

        x += beam->l();
    }
    auto sx = to_sx(x);
    auto sy = to_sy(y);

    painter.drawEllipse(sx - 5, sy, 10, 10);
    painter.drawLine(sx - 10, sy + 10, sx + 10, sy + 10);
}

void BeamView::drawLoads(QPainter& painter)
{
    auto x = -m_beamModel->length() / 2.0;
    auto y = 0.0;

    for (auto& beam : m_beamModel->beams())
    {
        auto sx = to_sx(x);
        auto sy = to_sy(y);

        painter.drawRect(sx, sy - 50 - std::abs(beam->q()) * m_loadScaleFactor, beam->l() * m_scaleFactor,
            std::abs(beam->q()) * m_loadScaleFactor);

        if (beam->q() > 0)
            this->drawLineWithArrow(painter, to_sx(x + beam->l() / 2.0), sy - 50, to_sx(x + beam->l() / 2.0),
                sy - 50 - std::abs(beam->q()) * m_loadScaleFactor);
        else
            this->drawLineWithArrow(painter, to_sx(x + beam->l() / 2.0),
                sy - 50 - std::abs(beam->q()) * m_loadScaleFactor, to_sx(x + beam->l() / 2.0),
                sy - 50);

        x += beam->l();
    }
    // painter.drawEllipse(sx - 5, sy, 10, 10);
}

void BeamView::drawDimensions(QPainter& painter)
{
}

void BeamView::drawDeflections(QPainter& painter)
{
    auto x = -m_beamModel->length() / 2.0;
    auto y = 0.0;

    for (auto& beam : m_beamModel->beams())
    {
        QPolygonF pl;
        pl.clear();
        for (auto i = 0; i < beam->evalCount(); i++)
        {
            // auto M = beam->M(i);
            // auto V = beam->V(i);
            auto lx0 = beam->x(i);

            QPointF p(to_sx(x + lx0), to_sy(0.0) - beam->v(i) * m_deflectionScaleFactor);
            pl << p;
        }
        painter.drawPolyline(pl);

        x += beam->l();
    }
}

void BeamView::drawM(QPainter& painter)
{
    auto x = -m_beamModel->length() / 2.0;
    auto y = 0.0;

    for (auto& beam : m_beamModel->beams())
    {
        QPolygonF pl;
        pl.clear();
        for (auto i = 0; i < beam->evalCount(); i++)
        {

            auto lx0 = beam->x(i);

            QPointF p(to_sx(x + lx0), to_sy(0.0) + beam->M(i) * m_MscaleFactor);
            pl << p;
        }
        pl << QPointF(to_sx(x + beam->x(beam->evalCount() - 1)), to_sy(0.0));
        pl << QPointF(to_sx(x + beam->x(0)), to_sy(0.0));

        painter.setPen(Qt::NoPen);
        painter.setBrush(m_momentBrush);

        painter.setOpacity(0.4);
        painter.drawPolygon(pl);
        painter.setOpacity(1.0);

        painter.setPen(m_pen);
        painter.setBrush(m_brush);

        x += beam->l();
    }
}

void BeamView::drawV(QPainter& painter)
{
    auto x = -m_beamModel->length() / 2.0;
    auto y = 0.0;

    for (auto& beam : m_beamModel->beams())
    {
        QPolygonF pl;
        pl.clear();
        for (auto i = 0; i < beam->evalCount(); i++)
        {
            // auto M = beam->M(i);
            // auto V = beam->V(i);
            auto lx0 = beam->x(i);

            QPointF p(to_sx(x + lx0), to_sy(0.0) + beam->V(i) * m_VscaleFactor);
            pl << p;
        }
        pl << QPointF(to_sx(x + beam->x(beam->evalCount() - 1)), to_sy(0.0));
        pl << QPointF(to_sx(x + beam->x(0)), to_sy(0.0));

        painter.setPen(Qt::NoPen);
        painter.setBrush(m_shearBrush);

        painter.setOpacity(0.4);
        painter.drawPolygon(pl);
        painter.setOpacity(1.0);

        painter.setPen(m_pen);
        painter.setBrush(m_brush);

        x += beam->l();
    }
}

bool BeamAnalysis::BeamView::isDarkModePalette()
{
    const QPalette palette = QApplication::palette();
    const QColor windowColor = palette.color(QPalette::Window);

    // Calculate relative luminance
    // Using perceived brightness formula: (R * 0.299 + G * 0.587 + B * 0.114)
    double luminance = (windowColor.red() * 0.299 + windowColor.green() * 0.587 + windowColor.blue() * 0.114) / 255.0;

    return luminance < 0.5;
}
