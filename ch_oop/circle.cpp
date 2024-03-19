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

bool Circle::operator==(const Circle& other) const
{
	return false;
}

Circle::Circle(const Circle& other)
	:Shape(other)
	, m_radius(other.m_radius)
{
}

Circle& Circle::operator=(const Circle& other)
{
	if (this != &other)
	{
		Shape::operator=(other);
		m_radius = other.m_radius;
	}
	return *this;
}

Circle::Circle(Circle&& other)
	:Shape(other)
	, m_radius(other.m_radius)
{
	other.m_radius = 0;
}

Circle& Circle::operator=(Circle&& other)
{
	if (this != &other)
	{
		Shape::operator=(other);
		m_radius = other.m_radius;
		other.m_radius = 0;
	}
	return *this;
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
	return pow(m_radius, 2) * pi;
}

double Circle::radius() const
{
	return m_radius;
}

void Circle::setRadius(double radius)
{
	m_radius = radius;
}

