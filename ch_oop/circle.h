#pragma once

#include "shape.h"

class Circle : public Shape {
private:
    double m_radius;
public:
    Circle(double x = 0.0, double y = 0.0, double radius = 1.0);
    bool operator==(const Circle& other) const;
    Circle(const Circle& other);
    Circle& operator=(const Circle& other);
    Circle(Circle&& other);
    Circle& operator=(Circle&& other);

    virtual ~Circle();

    virtual void print() const override;
    virtual double area() const override;
    virtual void draw() const override;
    
    double radius() const;
    void setRadius(double radius);
};