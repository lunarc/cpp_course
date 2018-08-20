#ifndef SUN_H
#define SUN_H

#include "base.h"
#include "vec3d.h"
#include "planet.h"

class Sun : public Base {
private:
    double m_mass;
    Vec3d m_loc;
    double m_G;
public:
    Sun(double m, double x, double y, double z);

    Vec3d attract(Planet* m);

    Vec3d location();

    double mass();

};

#endif // SUN_H
