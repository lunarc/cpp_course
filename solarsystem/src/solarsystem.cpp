#include "solarsystem.h"
#include "utils.h"
#include "vec3d.h"

#include <iostream>
#include <cmath>

using namespace std;

SolarSystem::SolarSystem(int n, int m)
:Base()
{
    m_nPlanets = n;
    m_nSuns = m;
    m_planetRadiusMin = 30.0;
    m_planetRadiusMax = 100.0;
    m_planetSpeedMin = 10.0;
    m_planetSpeedMax = 20.0;
    m_planetMassMin = 0.1;
    m_planetMassMax = 2.0;

    this->init();
}

SolarSystem::~SolarSystem()
{
    this->clear();
}

void SolarSystem::init()
{
    this->clear();

    for (int i = 0; i<m_nPlanets; i++)
    {
        double r = random(m_planetRadiusMin, m_planetRadiusMax);
        double v = random(m_planetSpeedMin, m_planetSpeedMax);
        double alfa = random(0.0, 2 * 3.14159);
        double x = r * cos(alfa);
        double y = r * sin(alfa);
        double vx = -v * sin(alfa);
        double vy = v * cos(alfa);
        Planet* planet = new Planet(random(m_planetMassMin, m_planetMassMax), x, 0.0, y);
        planet->setVelocity(vx, 0.0, vy);
        m_planets.push_back(planet);
    }

    for (int i = 0; i<m_nSuns; i++)
    {
        Sun* sun = new Sun(random(10, 20), random(-40.0 / 2, 40.0 / 2), 0, random(-40.0 / 2, 40.0 / 2));
        m_suns.push_back(sun);
    }
}

void SolarSystem::clear()
{
    //for (Planet* planet : m_planets)
    for (auto it = m_planets.begin(); it != m_planets.end(); it++)
        delete *it;

    m_planets.clear();

    //for (Planet* planet : m_planets)
    for (auto it = m_suns.begin(); it != m_suns.end(); it++)
        delete *it;

    m_suns.clear();
}

void SolarSystem::update(double dt)
{
    for (Planet* planet : m_planets)
    {
        for (Sun* sun : m_suns)
        {
            Vec3d force = sun->attract(planet);
            planet->applyForce(force);
        }
        planet->update(dt);
    }
}

int SolarSystem::planetCount()
{
    return m_planets.size();
}

int SolarSystem::sunCount()
{
    return m_suns.size();
}

void SolarSystem::setSize(int planets, int suns)
{
    m_nPlanets = planets;
    m_nSuns = suns;
}

Planet* SolarSystem::planetAt(int idx)
{
    if ((idx >= 0) && (idx < m_planets.size()))
        return m_planets[idx];
    else
        return nullptr;
}

Sun * SolarSystem::sunAt(int idx)
{
    if ((idx >= 0) && (idx < m_suns.size()))
        return m_suns[idx];
    else
        return nullptr;
}

void SolarSystem::setPlanetRadiusMax(double value)
{
    m_planetRadiusMax = value;
}

void SolarSystem::setPlanetRadiusMin(double value)
{
    m_planetRadiusMin = value;
}

void SolarSystem::setPlanetSpeedMax(double value)
{
    m_planetSpeedMax = value;
}

void SolarSystem::setPlanetSpeedMin(double value)
{
    m_planetSpeedMin = value;
}

void SolarSystem::setPlanetMassMax(double value)
{
    m_planetMassMax = value;
}

void SolarSystem::setPlanetMassMin(double value)
{
    m_planetMassMin = value;
}

double SolarSystem::planetRadiusMax()
{
    return m_planetRadiusMax;
}

double SolarSystem::planetRadiusMin()
{
    return m_planetRadiusMin;
}

double SolarSystem::planetSpeedMax()
{
    return m_planetSpeedMax;
}

double SolarSystem::planetSpeedMin()
{
    return m_planetSpeedMin;
}

double SolarSystem::planetMassMax()
{
    return m_planetMassMax;
}

double SolarSystem::planetMassMin()
{
    return m_planetMassMin;
}
