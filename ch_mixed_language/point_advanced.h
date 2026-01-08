#pragma once

#include <vector>
#include <cmath>
#include <string>

class Point {
    double x_, y_;
public:
    Point(double x, double y) : x_(x), y_(y) {}
    
    double distance_to(const Point& other) const;
    
    double x() const { return x_; }
    double y() const { return y_; }
    
    void set_x(double x) { x_ = x; }
    void set_y(double y) { y_ = y; }
    
    std::string to_string() const;
};

class PointCloud {
    std::vector<Point> points_;
public:
    PointCloud() = default;
    
    void add_point(const Point& p);
    void add_point(double x, double y);
    
    size_t size() const { return points_.size(); }
    const Point& get_point(size_t index) const;
    
    double total_distance() const;
    Point centroid() const;
    
    const std::vector<Point>& get_points() const { return points_; }
};
