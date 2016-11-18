#include <boost/python.hpp>

#include <iostream>

using namespace std;

class Particle {
private:
    double m_x;
    double m_y;
    double m_mass;
public:
    Particle(double x, double y);
    
    void show();
    void move(double dx, double dy);
    
    void setPosition(double x, double y);
    double x();
    double y();
    
    void setMass(double m);
    double mass();
};

Particle::Particle(double x, double y)
{
    m_x = x;
    m_y = y;
    m_mass = 1.0;
}

void Particle::show()
{
    cout << "x = " << m_x << ", y = " << m_y << endl;
    cout << "mass = " << m_mass << endl;
}

void Particle::move(double dx, double dy)
{
    m_x += dx;
    m_y += dy;
}

void Particle::setPosition(double x, double y)
{
    m_x = x;
    m_y = y;
}

double Particle::x()
{
    return m_x;
}

double Particle::y()
{
    return m_y;
}

void Particle::setMass(double m)
{
    m_mass = m;
}

double Particle::mass()
{
    return m_mass;
}  

BOOST_PYTHON_MODULE(particles)
{
    using namespace boost::python;
    
    class_<Particle>("Particle", init<double, double>())
        .def("show", &Particle::show)
        .def("move", &Particle::move)
        .def("setPosition", &Particle::setPosition)
        .def("x", &Particle::x)
        .def("y", &Particle::y)
        .def("setMass", &Particle::setMass)
        .def("mass", &Particle::mass)
    ;
}
