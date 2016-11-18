#include <iostream>

using namespace std;

class Point {
private:
    double m_x;
    double m_y;
public:
    Point(double x, double y);
    
    void print();
    
    void setPosition(double x, double y);
    double x();
    double y();
};

Point::Point(double x, double y)
{
    m_x = x;
    m_y = y;
}

void Point::print()
{
    cout << "x = " << m_x << ", y = " << m_y << endl;
}

int main()
{
    Point p0 = Point(0.0, 0.0);
    Point p1 = Point(1.0, 1.0);
    
    p0.print();
    p1.print();
}