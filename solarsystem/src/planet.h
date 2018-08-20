#ifndef PLANET_H
#define PLANET_H

#include "base.h"
#include "vec3d.h"

class Planet : public Base {
protected:
    Vec3d m_loc;
    Vec3d m_vel;
    Vec3d m_acc;
    double m_mass;
public:
    Planet(const Planet& planetCopy);
    Planet(double m, double x, double y, double z);

    void applyForce(const Vec3d& force);
    void update(double dt);

    void setVelocity(double x, double y, double z);

    Vec3d location();
    double mass();

};

#endif // PLANET_H
