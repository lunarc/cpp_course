#pragma once

#include "shape.h"

class Point : public Shape {
public:
    Point(double x, double y);
    virtual ~Point();
};