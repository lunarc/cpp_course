#include <print>

class Point {
private:
    double m_x{};
    double m_y{};
public:
    Point(double x = 0.0, double y = 0.0) noexcept;
    
    void print() const;
    
    void setPos(double x, double y) noexcept;
    [[nodiscard]] double x() const noexcept;
    [[nodiscard]] double y() const noexcept;
};

Point::Point(double x, double y) noexcept
    : m_x{x}, m_y{y}
{
}

void Point::print() const
{
    std::print("Point coordinates: x = {}, y = {}\n", m_x, m_y);
}

void Point::setPos(double x, double y) noexcept
{
    m_x = x;
    m_y = y;
}

double Point::x() const noexcept
{
    return m_x;
}

double Point::y() const noexcept
{
    return m_y;
}

int main()
{
    Point p0{0.0, 0.0};
    Point p1{1.0, 1.0};
    
    p0.print();
    p1.print();
}