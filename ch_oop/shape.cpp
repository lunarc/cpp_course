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
    cout << "Shape type: " << m_name << endl;
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
