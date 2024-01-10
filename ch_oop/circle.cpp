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
    cout << "Circle destructor called." << endl;
}

void Circle::print() const
{
    Shape::print();
    cout << "radius = " << m_radius << endl;
}

double Circle::area() const
{
	double pi = 4 * std::atan(1);
    return pow(m_radius,2)*pi;
}

double Circle::radius() const
{
    return m_radius;
}

void Circle::setRadius(double radius)
{
    m_radius = radius;
}

