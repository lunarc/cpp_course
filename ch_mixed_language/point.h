#pragma once

#ifdef __cplusplus

#include <vector>
#include <cmath>

class Point {
    double x_, y_;
public:
    Point(double x, double y) : x_(x), y_(y) {}
    double distance_to(const Point& other) const;
};

#endif

// C-compatible wrapper

#ifdef __cplusplus
extern "C" {
#endif

// Opaque handle for C code

typedef void* PointHandle;
    
PointHandle point_create(double x, double y);
void point_destroy(PointHandle handle);
double point_distance(PointHandle p1, PointHandle p2);

#ifdef __cplusplus 
}
#endif