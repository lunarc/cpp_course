#include "point.h"

#include <print>

Point::Point(double x, double y)
:Shape(x, y)
{
    this->setName("Point");
}

Point::~Point()
{
    std::print("Point destructor called.\n");
}

double Point::area() const
{
    return 0.0;
}
