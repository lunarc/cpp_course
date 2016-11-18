#include "rectangle.h"

#include <iostream>
#include <cmath>

using namespace std;

Rectangle::Rectangle(double x, double y, double width, double height)
:Shape(x, y)
{
    this->setName("Rectangle");
    m_width = width;
    m_height = height;
}

Rectangle::~Rectangle()
{
    cout << "Rectangle destructor called." << endl;
}


void Rectangle::print()
{
    Shape::print();
    cout << "width = " << m_width << endl;
    cout << "height = " << m_height << endl;
}

double Rectangle::area()
{
    return m_width*m_height;
}

double Rectangle::width()
{
    return m_width;
}

void Rectangle::setWidth(double width)
{
    m_width = width;
}

void Rectangle::setHeight(double height)
{
    m_height = height;
}

