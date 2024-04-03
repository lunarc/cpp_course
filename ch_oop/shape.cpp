#include "shape.h"

#include <iostream>

using namespace std;

Shape::Shape()
: m_x(0.0), m_y(0.0), m_name("Shape")
{
    cout << "Shape created (default)." << endl;
}

Shape::Shape(double x, double y)
{
    cout << "Shape created." << endl;
    m_x = x;
    m_y = y;
    m_name = "Shape";
}

Shape::Shape(const Shape& other)
: m_x(other.m_x), m_y(other.m_y), m_name(other.m_name)
{
}

Shape& Shape::operator=(const Shape& other)
{
    m_x = other.m_x;
    m_y = other.m_y;
    m_name = other.m_name;
    return *this;
}

Shape::Shape(Shape&& other) noexcept
{
    m_x = other.m_x;
	m_y = other.m_y;
	m_name = other.m_name;
	other.m_x = 0.0;
	other.m_y = 0.0;
	other.m_name = "Shape";
}

Shape& Shape::operator=(Shape&& other) noexcept
{
    m_x = other.m_x;
	m_y = other.m_y;
	m_name = other.m_name;
	other.m_x = 0.0;
	other.m_y = 0.0;
	other.m_name = "Shape";
	return *this;
}

bool Shape::operator==(const Shape& other) const
{
	return m_x == other.m_x && m_y == other.m_y && m_name == other.m_name;
}

Shape::~Shape()
{
    cout << "Shape destructor called." << endl;
}

void Shape::print() const
{
    cout << "--------------------------" << endl;
    cout << "Shape name: " << m_name << endl;
    cout << "x = " << m_x << ", y = " << m_y << endl;
    cout << "area = " << this->area() << endl;
}

void Shape::setPosition(double x, double y)
{
    m_x = x;
    m_y = y;
}

double Shape::x() const
{
	return m_x;
}

void Shape::draw() const
{
    cout << "Drawing a shape." << endl;
    cout << "Using fill color: ";
    cout << "(" << m_fillColor[0] << ", " << m_fillColor[1] << ", " << m_fillColor[2] << ", " << m_fillColor[3] << ")" << endl;
    cout << "Using line color: ";
    cout << "(" << m_lineColor[0] << ", " << m_lineColor[1] << ", " << m_lineColor[2] << ", " << m_lineColor[3] << ")" << endl;
    cout << "Position: (" << m_x << ", " << m_y << ")" << endl;
}

double Shape::y() const
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

void Shape::setFillColor(double r, double g, double b, double a)
{
    m_fillColor[0] = r;
	m_fillColor[1] = g;
	m_fillColor[2] = b;
	m_fillColor[3] = a;
}

void Shape::setLineColor(double r, double g, double b, double a)
{
    m_lineColor[0] = r;
	m_lineColor[1] = g;
	m_lineColor[2] = b;
	m_lineColor[3] = a;
}

void Shape::getFillColor(double& r, double& g, double& b, double& a) const
{
    r = m_fillColor[0];
	g = m_fillColor[1];
	b = m_fillColor[2];
	a = m_fillColor[3];
}

void Shape::getLineColor(double& r, double& g, double& b, double& a) const
{
    r = m_lineColor[0];
	g = m_lineColor[1];
	b = m_lineColor[2];
	a = m_lineColor[3];
}
