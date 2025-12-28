#pragma once

#include "shape.h"

class Circle : public Shape {
private:
    double m_radius;
public:
    Circle(double x = 0.0, double y = 0.0, double radius = 1.0);
    bool operator==(const Circle& other) const = default;
    Circle(const Circle& other) = default;
    Circle& operator=(const Circle& other) = default;
    Circle(Circle&& other) noexcept = default;
    Circle& operator=(Circle&& other) noexcept = default;

    ~Circle() override;

    void print() const override;
    [[nodiscard]] double area() const override;
    void draw() const override;
    
    [[nodiscard]] double radius() const noexcept;
    void setRadius(double radius) noexcept;
};