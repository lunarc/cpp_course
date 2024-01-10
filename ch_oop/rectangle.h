#pragma once

#include "shape.h"

class Rectangle : public Shape {
private:
    double m_width;
    double m_height;
public:
    Rectangle();
    explicit Rectangle(double x, double y, double width=1.0, double height=1.0);
    Rectangle(const Rectangle& other);
    bool operator==(const Rectangle& other) const = default;
    virtual ~Rectangle();
    
    void print() const override;
    double area() const override;
    
    double width() const;
    void setWidth(double width);
    
    double height() const;
    void setHeight(double height);    
};