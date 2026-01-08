#include "point_advanced.h"
#include <sstream>
#include <stdexcept>

double Point::distance_to(const Point& other) const {
    double dx = x_ - other.x_;
    double dy = y_ - other.y_;
    return std::sqrt(dx * dx + dy * dy);
}

std::string Point::to_string() const {
    std::ostringstream oss;
    oss << "Point(" << x_ << ", " << y_ << ")";
    return oss.str();
}

void PointCloud::add_point(const Point& p) {
    points_.push_back(p);
}

void PointCloud::add_point(double x, double y) {
    points_.emplace_back(x, y);
}

const Point& PointCloud::get_point(size_t index) const {
    if (index >= points_.size()) {
        throw std::out_of_range("Index out of range");
    }
    return points_[index];
}

double PointCloud::total_distance() const {
    if (points_.size() < 2) {
        return 0.0;
    }
    
    double total = 0.0;
    for (size_t i = 0; i < points_.size() - 1; ++i) {
        total += points_[i].distance_to(points_[i + 1]);
    }
    return total;
}

Point PointCloud::centroid() const {
    if (points_.empty()) {
        return Point(0.0, 0.0);
    }
    
    double sum_x = 0.0;
    double sum_y = 0.0;
    
    for (const auto& p : points_) {
        sum_x += p.x();
        sum_y += p.y();
    }
    
    return Point(sum_x / points_.size(), sum_y / points_.size());
}
