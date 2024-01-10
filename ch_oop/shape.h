#pragma once

#include <string>

class Shape {
private:
    double m_x;
    double m_y;
    std::string m_name;
public:
    Shape();
    Shape(double x, double y);
    Shape(const Shape& other);
    bool operator==(const Shape& other) const = default;
    virtual ~Shape();
    
    virtual void print() const;
    virtual double area() const = 0; 
    
    void setPosition(double x, double y);
    double x() const;
    double y() const;
    
    void setName(const std::string& name);
    std::string name() const;
};