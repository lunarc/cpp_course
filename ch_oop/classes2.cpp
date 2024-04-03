#include <iostream>

using namespace std;

class Vector {
private:
	double m_x{};
	double m_y{};
public:
	Vector(double x = 0.0, double y = 0.0);
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);

	Vector operator+(const Vector& other) const;
	Vector operator-(const Vector& other) const;
	Vector operator*(float scalar) const;

	double dot(const Vector& other) const;
	double cross(const Vector& other) const;
	double length() const;

	void print() const;

	void set(double x, double y);
	double x() const;
	double y() const;
};

Vector::Vector(double x, double y)
	: m_x(x), m_y(y)
{
	std::cout << "Constructor called" << std::endl;
}

Vector::Vector(const Vector& other)
	: m_x(other.m_x), m_y(other.m_y)
{
	std::cout << "Copy constructor called" << std::endl;
}

Vector& Vector::operator=(const Vector& other)
{
	std::cout << "Copy assignment called" << std::endl;
	m_x = other.m_x;
	m_y = other.m_y;
	return *this;
}

// Addition of two vectors
Vector Vector::operator+(const Vector& other) const {
	return Vector(m_x + other.m_x, m_y + other.m_y);
}

// Subtraction of two vectors
Vector Vector::operator-(const Vector& other) const {
	return Vector(m_x - other.m_x, m_y - other.m_y);
}

// Scalar multiplication of a vector
Vector Vector::operator*(float scalar) const {
	return Vector(m_x * scalar, m_y * scalar);
}

// Dot product of two vectors
double Vector::dot(const Vector& other) const {
	return m_x * other.m_x + m_y * other.m_y;
}

// Cross product of two vectors
double Vector::cross(const Vector& other) const {
	return m_x * other.m_y - m_y * other.m_x;
}

double Vector::length() const
{
	return std::sqrt(this->dot(*this));
}

void Vector::print() const
{
	cout << "(" << m_x << ", " << m_y << ")\n";
}

void Vector::set(double x, double y)
{
	m_x = x;
	m_y = y;
}

double Vector::x() const
{
	return m_x;
}

double Vector::y() const
{
	return m_y;
}

int main()
{
	Vector v0{ 0.0, 0.0 };
	Vector v1{ 1.0, 1.0 };
	Vector v2 = v1;
	v0 = v1;

	auto v4 = v0 + v1;
	v4.print();

	cout << "v0.x() = " << v0.x() << endl;
	cout << "v0.y() = " << v0.y() << endl;

	v1.set(0.5, 0.5);

	cout << "v1.x() = " << v1.x() << endl;
	cout << "v1.y() = " << v1.y() << endl;

	Vector v5{ 1.0, 0.0 };
	Vector v6{ 0.0, 1.0 };

	cout << "v5.dot(v6) = " << v5.dot(v6) << endl;
	cout << "v5.cross(v6) = " << v5.cross(v6) << endl;
	cout << "v5.length() = " << v5.length() << endl;

	std::unique_ptr<Vector> v3 = std::make_unique<Vector>(1.0, 1.0);
	v3->set(1.5, 1.5);
	cout << "v3->x() = " << v3->x() << endl;
	cout << "v3->y() = " << v3->y() << endl;



	return 0;
}