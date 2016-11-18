#include "circle.h"

#include <iostream>
#include <cmath>

using namespace std;

Circle::Circle(double x, double y, double radius)
:Shape(x, y)
{
    this->setName("Circle");
    m_radius = radius;
}

Circle::~Circle()
{
}

void Circle::print()
{
    Shape::print();
    cout << "radius = " << m_radius << endl;
}

double Circle::area()
{
    return pow(m_radius,2)*M_PI;
}

double Circle::radius()
{
    return m_radius;
}

void Circle::setRadius(double radius)
{
    m_radius = radius;
}

