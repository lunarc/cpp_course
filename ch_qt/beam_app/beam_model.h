#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Beam {
private:
    double m_l;
    double m_E;
    double m_A;
    double m_I;
    double m_q;
public:
    Beam(double l=1.0, double E=2.1e9, double A=0.01, double I=8.33e-6, double q=1.0e3);

    static std::shared_ptr<Beam> create(double l=1.0, double E=2.1e9, double A=0.01, double I=8.33e-6, double q=1.0e3);

    double l();
    void l(double value);

    double E();
    void E(double value);

    double A();
    void A(double value);

    double I();
    void I(double value);

    double q();
    void q(double value);
};

typedef std::shared_ptr<Beam> BeamPtr;

class BeamModel {
private:
    std::vector<BeamPtr> m_beams;

    void init_beams(int nBeams);
public:
    BeamModel(int nBeams);

    static std::shared_ptr<BeamModel> create(int nBeams);

    void add(double l=1.0);
    void removeLast();

    double length();
    double maxLoad();

    const std::vector<BeamPtr>& beams();

    BeamPtr beam(int idx);

    int beam_pos_from_x(double x);
};

typedef std::shared_ptr<BeamModel> BeamModelPtr;
