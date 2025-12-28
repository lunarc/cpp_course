#pragma once

#include <string>
#include <array>

class Shape {
private:
    double m_x{};
    double m_y{};
    std::array<double, 4> m_fillColor{ 1.0, 0.0, 0.0, 1.0};
    std::array<double, 4> m_lineColor{ 0.0, 0.0, 0.0, 1.0};
    std::string m_name{};
public:
    Shape();
    Shape(double x, double y);
    Shape(const Shape& other) = default;
    Shape& operator=(const Shape& other) = default;
    Shape(Shape&& other) noexcept = default;
    Shape& operator=(Shape&& other) noexcept = default;

    bool operator==(const Shape& other) const = default;
    virtual ~Shape();
    
    virtual void print() const;
    [[nodiscard]] virtual double area() const;
    virtual void draw() const;
    
    void setPosition(double x, double y) noexcept;
    [[nodiscard]] double x() const noexcept;
    [[nodiscard]] double y() const noexcept;

    void setFillColor(double r, double g, double b, double a) noexcept;
    void setLineColor(double r, double g, double b, double a) noexcept;

    [[nodiscard]] std::array<double, 4> getFillColor() const noexcept;
    [[nodiscard]] std::array<double, 4> getLineColor() const noexcept;

    void setName(const std::string& name);
    [[nodiscard]] std::string name() const;
};