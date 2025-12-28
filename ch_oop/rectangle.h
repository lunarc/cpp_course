#pragma once

#include "shape.h"

class Rectangle : public Shape {
private:
    double m_width;
    double m_height;
public:
    Rectangle();
    explicit Rectangle(double x, double y, double width=1.0, double height=1.0);
    Rectangle(const Rectangle& other) = default;
    Rectangle& operator=(const Rectangle& other) = default;
    Rectangle(Rectangle&& other) noexcept = default;
    Rectangle& operator=(Rectangle&& other) noexcept = default;
    bool operator==(const Rectangle& other) const = default;
    ~Rectangle() override;
    
    void print() const override;
    [[nodiscard]] double area() const override;
    
    [[nodiscard]] double width() const noexcept;
    void setWidth(double width) noexcept;
    
    [[nodiscard]] double height() const noexcept;
    void setHeight(double height) noexcept;
};