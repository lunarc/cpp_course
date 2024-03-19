#include <iostream>

using namespace std;

class Point {
private:
	double m_x{};
	double m_y{};
public:
	Point(double x = 0.0, double y = 0.0);

	void print() const;

	void setPosition(double x, double y);
	double x() const;
	double y() const;
};

Point::Point(double x, double y)
	: m_x(x), m_y(y)
{
}

void Point::print() const
{
	cout << "x = " << m_x << ", y = " << m_y << endl;
}

void Point::setPosition(double x, double y)
{
	m_x = x;
	m_y = y;
}

double Point::x() const
{
	return m_x;
}

double Point::y() const
{
	return m_y;
}

int main()
{
	Point p0 = Point(0.0, 0.0);
	Point p1 = Point(1.0, 1.0);

	cout << "p0.x() = " << p0.x() << endl;
	cout << "p0.y() = " << p0.y() << endl;

	p1.setPosition(0.5, 0.5);

	cout << "p1.x() = " << p1.x() << endl;
	cout << "p1.y() = " << p1.y() << endl;

	Point* p3 = new Point(2.0, 2.0);
	p3->setPosition(1.5, 1.5);
	cout << "p3->x() = " << p3->x() << endl;
}