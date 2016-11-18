#pragma once

#include "shape.h"

class Circle : public Shape {
private:
    double m_radius;
public:
    Circle(double x, double y, double radius = 1.0);
    virtual ~Circle();
    
    virtual void print();
    virtual double area();
    
    double radius();
    void setRadius(double radius);
};