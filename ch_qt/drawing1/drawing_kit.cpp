#include "drawing_kit.h"

#include <QPainter>

namespace DrawingKit
{

void DrawableBase::doDraw(QPainter& painter)
{
}

DrawableBase::DrawableBase()
    : m_x { 0.0 }
    , m_y { 0.0 }
{
    m_pen.setColor(QColor(0, 0, 0));
    m_pen.setWidth(2);
    m_brush.setColor(QColor(255, 255, 255));
    m_brush.setStyle(Qt::SolidPattern);
}

void DrawableBase::setPos(float x, float y)
{
    m_x = x;
    m_y = y;
}

void DrawableBase::x(float value)
{
    m_x = value;
}

void DrawableBase::y(float value)
{
    m_y = value;
}

float DrawableBase::x()
{
    return m_x;
}

float DrawableBase::y()
{
    return m_y;
}

void DrawableBase::setPen(QPen pen)
{
    m_pen = pen;
}

void DrawableBase::setBrush(QBrush brush)
{
    m_brush = brush;
}

void DrawableBase::setPenColor(int r, int g, int b, int a)
{
    m_pen.setColor(QColor(r, g, b, a));
}

void DrawableBase::setFillColor(int r, int g, int b, int a)
{
    m_brush.setColor(QColor(r, g, b, a));
}

void DrawableBase::setPenWidth(float width)
{
    m_pen.setWidth(width);
}

void DrawableBase::draw(QPainter& painter)
{
    painter.setBrush(m_brush);
    painter.setPen(m_pen);
    painter.translate(m_x, m_y);
    this->doDraw(painter);
    painter.resetTransform();
}

std::shared_ptr<Point> Point::create()
{
    return std::make_shared<Point>();
}

void Point::doDraw(QPainter& painter)
{
    painter.drawPoint(0, 0);
}

Ellipse::Ellipse()
    : m_width { 50.0 }
    , m_height { 50.0 }
{
}

std::shared_ptr<Ellipse> Ellipse::create()
{
    return std::make_shared<Ellipse>();
}

void Ellipse::setSize(float width, float height)
{
    m_width = width;
    m_height = height;
}

float Ellipse::width()
{
    return m_width;
}

float Ellipse::height()
{
    return m_height;
}

void Ellipse::width(float value)
{
    m_width = value;
}

void Ellipse::height(float value)
{
    m_height = value;
}

void Ellipse::doDraw(QPainter& painter)
{
    painter.drawEllipse(0, 0, m_width, m_height);
}

std::shared_ptr<Group> Group::create()
{
    return std::make_shared<Group>();
}

void Group::add(DrawableBasePtr shape)
{
    m_shapes.push_back(shape);
}

void Group::clear()
{
    m_shapes.clear();
}

void Group::doDraw(QPainter& painter)
{
    for (auto shape : m_shapes)
        shape->draw(painter);
}

Rectangle::Rectangle()
{
}

std::shared_ptr<Rectangle> Rectangle::create()
{
    return std::make_shared<Rectangle>();
}

void Rectangle::setSize(float width, float height)
{
    m_width = width;
    m_height = height;
}

float Rectangle::width()
{
    return m_width;
}

float Rectangle::height()
{
    return m_height;
}

void Rectangle::width(float value)
{
    m_width = value;
}

void Rectangle::height(float value)
{
    m_height = value;
}

void Rectangle::doDraw(QPainter& painter)
{
    painter.drawRect(-m_width / 2.0, m_height / 2.0, m_width, m_height);
}

}; // namespace DrawingKit
