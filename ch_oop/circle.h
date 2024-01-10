#pragma once

#include "shape.h"

class Circle : public Shape {
private:
    double m_radius;
public:
    Circle() = default;
    Circle(double x, double y, double radius = 1.0);
    bool operator==(const Circle& other) const = default;
    virtual ~Circle();

    virtual void print() const override;
    virtual double area() const override;
    
    double radius() const;
    void setRadius(double radius);


};