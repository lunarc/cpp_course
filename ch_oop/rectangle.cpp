#include "rectangle.h"

#include <print>
#include <cmath>

Rectangle::Rectangle()
:Shape(), m_width(1.0), m_height(1.0)
{
    std::print("Rectangle created (default).\n");
    this->setName("Rectangle");
}

Rectangle::Rectangle(double x, double y, double width, double height)
:Shape(x, y), m_width(width), m_height(height)
{
    this->setName("Rectangle");
}

Rectangle::~Rectangle()
{
    std::print("Rectangle destructor called.\n");
}

void Rectangle::print() const
{
    Shape::print();
    std::print("width = {}\n", m_width);
    std::print("height = {}\n", m_height);
}

double Rectangle::area() const
{
    return m_width * m_height;
}

double Rectangle::width() const noexcept
{
    return m_width;
}

void Rectangle::setWidth(double width) noexcept
{
    m_width = width;
}

double Rectangle::height() const noexcept
{
    return m_height;
}

void Rectangle::setHeight(double height) noexcept
{
    m_height = height;
}

