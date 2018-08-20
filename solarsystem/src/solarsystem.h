 #pragma once

#include <vector>

#include "base.h"
#include "planet.h"
#include "sun.h"

class SolarSystem : public Base {
private:
    std::vector<Planet*> m_planets;
    std::vector<Sun*> m_suns;

    int m_nPlanets;
    int m_nSuns;

    double m_planetRadiusMin;
    double m_planetRadiusMax;
    double m_planetSpeedMin;
    double m_planetSpeedMax;
    double m_planetMassMin;
    double m_planetMassMax;
public:
    SolarSystem(int n = 100, int m=2);
    virtual ~SolarSystem();

    void init();
	void clear();
    int planetCount();
    int sunCount();

    void setSize(int planets, int suns);

    Planet* planetAt(int idx);
    Sun* sunAt(int idx);

	void update(double dt);	

    void setPlanetRadiusMax(double value);
    void setPlanetRadiusMin(double value);
    void setPlanetSpeedMax(double value);
    void setPlanetSpeedMin(double value);
    void setPlanetMassMax(double value);
    void setPlanetMassMin(double value);

    double planetRadiusMax();
    double planetRadiusMin();
    double planetSpeedMax();
    double planetSpeedMin();
    double planetMassMax();
    double planetMassMin();
};

