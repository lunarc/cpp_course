#pragma once

#include "shape.h"
#include <vector>

class Composite : public Shape {
private:
    std::vector<Shape*> m_shapes;
public:
    Composite(double x, double y);
    virtual ~Composite();
    
    virtual void print();
    virtual double area();
    
    void add(Shape* shape);
    void remove(Shape* shape);
    void clear();
    int count();
    
    Shape* at(int idx);
};