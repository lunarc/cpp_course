#pragma once

#include <string>

class Shape {
private:
    double m_x{};
    double m_y{};
    double m_fillColor[4]{ 1.0, 0.0, 0.0, 1.0};
    double m_lineColor[4]{ 0.0, 0.0, 0.0, 1.0};
    std::string m_name{};
public:
    Shape();
    Shape(double x, double y);
    Shape(const Shape& other);
    Shape& operator=(const Shape& other);
    Shape(Shape&& other) noexcept;
    Shape& operator=(Shape&& other) noexcept;

    bool operator==(const Shape& other) const;
    virtual ~Shape();
    
    virtual void print() const;
    virtual double area() const;
    virtual void draw() const;
    
    void setPosition(double x, double y);
    double x() const;
    double y() const;

    void setFillColor(double r, double g, double b, double a);
    void setLineColor(double r, double g, double b, double a);

    void getFillColor(double& r, double& g, double& b, double& a) const;
    void getLineColor(double& r, double& g, double& b, double& a) const;

    void setName(const std::string& name);
    std::string name() const;
};