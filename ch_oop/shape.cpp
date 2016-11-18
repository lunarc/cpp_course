#include "shape.h"

#include <iostream>

using namespace std;

Shape::Shape(double x, double y)
{
    cout << "Shape created." << endl;
    m_x = x;
    m_y = y;
    m_name = "Shape";
}

Shape::~Shape()
{
    cout << "Shape destructor called." << endl;
}

void Shape::print()
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

double Shape::x()
{
    return m_x;
}

double Shape::y()
{
    return m_y;
}

double Shape::area()
{
    return 0.0;
}

void Shape::setName(const std::string& name)
{
    m_name = name;
}

std::string Shape::name()
{
    return m_name;
}
