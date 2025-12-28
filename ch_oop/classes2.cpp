#include <memory>
#include <cmath>
#include <print>

class Vector {
private:
	double m_x{};
	double m_y{};
public:
	Vector(double x = 0.0, double y = 0.0) noexcept;
	Vector(const Vector& other);
	Vector(Vector&& other) noexcept = default;
	Vector& operator=(const Vector& other);
	Vector& operator=(Vector&& other) noexcept = default;
	~Vector() = default;

	[[nodiscard]] Vector operator+(const Vector& other) const noexcept;
	[[nodiscard]] Vector operator-(const Vector& other) const noexcept;
	[[nodiscard]] Vector operator*(double scalar) const noexcept;

	[[nodiscard]] double dot(const Vector& other) const noexcept;
	[[nodiscard]] double cross(const Vector& other) const noexcept;
	[[nodiscard]] double length() const noexcept;

	void print() const;

	constexpr void set(double x, double y) noexcept;
	[[nodiscard]] constexpr double x() const noexcept;
	[[nodiscard]] constexpr double y() const noexcept;
};

Vector::Vector(double x, double y) noexcept
	: m_x{x}, m_y{y}
{
	std::print("Constructor called\n");
}

Vector::Vector(const Vector& other)
	: m_x{other.m_x}, m_y{other.m_y}
{
	std::print("Copy constructor called\n");
}

Vector& Vector::operator=(const Vector& other)
{
	std::print("Copy assignment called\n");
	if (this != &other) {
		m_x = other.m_x;
		m_y = other.m_y;
	}
	return *this;
}

Vector Vector::operator+(const Vector& other) const noexcept
{
	return Vector(m_x + other.m_x, m_y + other.m_y);
}

Vector Vector::operator-(const Vector& other) const noexcept
{
	return Vector(m_x - other.m_x, m_y - other.m_y);
}

Vector Vector::operator*(double scalar) const noexcept
{
	return Vector(m_x * scalar, m_y * scalar);
}

double Vector::dot(const Vector& other) const noexcept
{
	return m_x * other.m_x + m_y * other.m_y;
}

double Vector::cross(const Vector& other) const noexcept
{
	return m_x * other.m_y - m_y * other.m_x;
}

double Vector::length() const noexcept
{
	return std::hypot(m_x, m_y);
}

void Vector::print() const
{
	std::print("({}, {})\n", m_x, m_y);
}

constexpr void Vector::set(double x, double y) noexcept
{
	m_x = x;
	m_y = y;
}

constexpr double Vector::x() const noexcept
{
	return m_x;
}

constexpr double Vector::y() const noexcept
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

	std::print("v0.x() = {}\n", v0.x());
	std::print("v0.y() = {}\n", v0.y());

	v1.set(0.5, 0.5);

	std::print("v1.x() = {}\n", v1.x());
	std::print("v1.y() = {}\n", v1.y());

	Vector v5{ 1.0, 0.0 };
	Vector v6{ 0.0, 1.0 };

	std::print("v5.dot(v6) = {}\n", v5.dot(v6));
	std::print("v5.cross(v6) = {}\n", v5.cross(v6));
	std::print("v5.length() = {}\n", v5.length());

	auto v3 = std::make_unique<Vector>(1.0, 1.0);
	v3->set(1.5, 1.5);
	std::print("v3->x() = {}\n", v3->x());
	std::print("v3->y() = {}\n", v3->y());

	return 0;
}