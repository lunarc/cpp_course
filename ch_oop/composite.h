#pragma once

#include "shape.h"
#include <vector>
#include <memory>

class Composite : public Shape {
private:
    std::vector< std::shared_ptr<Shape> > m_shapes;
public:
    Composite(double x, double y);
    virtual ~Composite();
    
    virtual void print() const override;
    virtual double area() const override;
    
    void add(Shape* shape);
    void remove(Shape* shape);
    void clear();
    size_t count();
    
    Shape* at(int idx);
};
