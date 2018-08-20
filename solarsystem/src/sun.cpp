#include "sun.h"

double constrain(double value, double minValue, double maxValue)
{
    if (value<minValue)
        return minValue;

    if (value>maxValue)
        return maxValue;

    return value;
}

Sun::Sun(double m, double x, double y, double z)
{
    m_loc.setComponents(x, y, z);
    m_mass = m;
    m_G = 10.0;
}

Vec3d Sun::attract(Planet* m)
{
    Vec3d force = m_loc - m->location();
    double d = force.length();
    d = constrain(d, 5.0, 25.0);
    double strength = (m_G * m_mass * m->mass()) / (d * d);
    return force * strength / d;
}

Vec3d Sun::location()
{
    return m_loc;
}

double Sun::mass()
{
    return m_mass;
}
