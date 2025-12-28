#pragma once

#include "shape.h"

class Point : public Shape {
public:
    Point() = default;
    Point(double x, double y);
    ~Point() override;

    [[nodiscard]] double area() const override;
};