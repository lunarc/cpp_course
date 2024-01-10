#include "rectangle.h"

#include <iostream>
#include <cmath>

using namespace std;

Rectangle::Rectangle()
:Shape(), m_width(1.0), m_height(1.0)
{
    cout << "Rectangle created (default)." << endl;
    this->setName("Rectangle");
}

Rectangle::Rectangle(double x, double y, double width, double height)
:Shape(x, y)
{
    this->setName("Rectangle");
    m_width = width;
    m_height = height;
}

Rectangle::Rectangle(const Rectangle& other)
{
	cout << "Rectangle created (copy)." << endl;
	this->setName(other.name());
	m_width = other.m_width;
	m_height = other.m_height;
}

Rectangle::~Rectangle()
{
    cout << "Rectangle destructor called." << endl;
}


void Rectangle::print() const
{
    Shape::print();
    cout << "width = " << m_width << endl;
    cout << "height = " << m_height << endl;
}

double Rectangle::area() const
{
    return m_width*m_height;
}

double Rectangle::width() const
{
    return m_width;
}

void Rectangle::setWidth(double width)
{
    m_width = width;
}

double Rectangle::height() const
{
    return 0.0;
}

void Rectangle::setHeight(double height)
{
    m_height = height;
}

