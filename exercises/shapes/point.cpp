#include "point.h"

#include <iostream>

using namespace std;

Point::Point(double x, double y)
:Shape(x, y)
{
    this->setName("Point");
}

Point::~Point()
{
}
