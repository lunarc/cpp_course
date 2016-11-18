#pragma once

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