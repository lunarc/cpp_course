#include "planet.h"

#include "utils.h"

Planet::Planet(const Planet& planetCopy)
{
    m_loc = planetCopy.m_loc;
    m_vel = planetCopy.m_vel;
    m_acc = planetCopy.m_acc;
    m_mass = planetCopy.m_mass;
}

Planet::Planet(double m, double x, double y, double z)
{
    m_loc.setComponents(x, y, z);
    m_vel.setComponents(random(-1.0, 1.0)*5, 0.0, random(-1.0, 1.0)*5);
    m_acc.setComponents(0.0, 0.0, 0.0);
    m_mass = m;
}

Vec3d Planet::location()
{
    return m_loc;
}

double Planet::mass()
{
    return m_mass;
}

void Planet::applyForce(const Vec3d& force)
{
    Vec3d a = force / m_mass;
    m_acc += a;
}

void Planet::update(double dt)
{
    m_vel += m_acc * dt;
    m_loc += m_vel * dt;
    m_acc.setComponents(0.0, 0.0, 0.0);
}

void Planet::setVelocity(double x, double y, double z)
{
    m_vel.setComponents(x, y, z);
}


