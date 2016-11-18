#pragma once

#include "shape.h"

class Rectangle : public Shape {
private:
    double m_width;
    double m_height;
public:
    Rectangle(double x, double y, double width=1.0, double height=1.0);
    virtual ~Rectangle();
    
    virtual void print();
    virtual double area();
    
    double width();
    void setWidth(double width);
    
    double height();
    void setHeight(double height);    
};