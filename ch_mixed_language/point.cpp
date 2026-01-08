#include "point.h"

double Point::distance_to(const Point& other) const {
    double dx = x_ - other.x_;
    double dy = y_ - other.y_;
    return std::sqrt(dx * dx + dy * dy);
}

extern "C" {
   
PointHandle point_create(double x, double y) {
    return new Point(x, y);
}

void point_destroy(PointHandle handle) {
    delete static_cast<Point*>(handle);
}

double point_distance(PointHandle p1, PointHandle p2) {
    Point* point1 = static_cast<Point*>(p1);
    Point* point2 = static_cast<Point*>(p2);
    return point1->distance_to(*point2);
}

}
