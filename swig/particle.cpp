#include "particle.h"

#include <iostream>

using namespace std;

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
