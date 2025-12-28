#include "shape.h"

#include <print>

Shape::Shape()
: m_x(0.0), m_y(0.0), m_name("Shape")
{
    std::print("Shape created (default).\n");
}

Shape::Shape(double x, double y)
: m_x(x), m_y(y), m_name("Shape")
{
    std::print("Shape created.\n");
}

Shape::~Shape()
{
    std::print("Shape destructor called.\n");
}

void Shape::print() const
{
    std::print("--------------------------\n");
    std::print("Shape name: {}\n", m_name);
    std::print("x = {}, y = {}\n", m_x, m_y);
    std::print("area = {}\n", this->area());
}

void Shape::setPosition(double x, double y) noexcept
{
    m_x = x;
    m_y = y;
}

double Shape::x() const noexcept
{
	return m_x;
}

void Shape::draw() const
{
    std::print("Drawing a shape.\n");
    std::print("Using fill color: ({}, {}, {}, {})\n", 
        m_fillColor[0], m_fillColor[1], m_fillColor[2], m_fillColor[3]);
    std::print("Using line color: ({}, {}, {}, {})\n", 
        m_lineColor[0], m_lineColor[1], m_lineColor[2], m_lineColor[3]);
    std::print("Position: ({}, {})\n", m_x, m_y);
}

double Shape::y() const noexcept
{
    return m_y;
}

double Shape::area() const
{
    return 0.0;
}

void Shape::setName(const std::string& name)
{
    m_name = name;
}

std::string Shape::name() const
{
    return m_name;
}

void Shape::setFillColor(double r, double g, double b, double a) noexcept
{
    m_fillColor[0] = r;
	m_fillColor[1] = g;
	m_fillColor[2] = b;
	m_fillColor[3] = a;
}

void Shape::setLineColor(double r, double g, double b, double a) noexcept
{
    m_lineColor[0] = r;
	m_lineColor[1] = g;
	m_lineColor[2] = b;
	m_lineColor[3] = a;
}

std::array<double, 4> Shape::getFillColor() const noexcept
{
    return m_fillColor;
}

std::array<double, 4> Shape::getLineColor() const noexcept
{
    return m_lineColor;
}
