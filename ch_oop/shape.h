#pragma once

#include <string>

class Shape {
private:
    double m_x;
    double m_y;
    std::string m_name;
public:
    Shape(double x, double y);
    virtual ~Shape();
    
    virtual void print();
    virtual double area();
    
    void setPosition(double x, double y);
    double x();
    double y();
    
    void setName(const std::string& name);
    std::string name();
};