#include "circle.h"

#include <print>
#include <cmath>
#include <numbers>

Circle::Circle(double x, double y, double radius)
	:Shape(x, y), m_radius(radius)
{
	this->setName("Circle");
}

Circle::~Circle()
{
	std::print("Circle destructor called.\n");
}

void Circle::print() const
{
	Shape::print();
	std::print("radius = {}\n", m_radius);
}

double Circle::area() const
{
	return m_radius * m_radius * std::numbers::pi;
}

void Circle::draw() const
{
	Shape::draw();
	std::print("Drawing a circle at: ({}, {})\n", x(), y());
	std::print("Circle radius: {}\n", m_radius);
}

double Circle::radius() const noexcept
{
	return m_radius;
}

void Circle::setRadius(double radius) noexcept
{
	m_radius = radius;
}

