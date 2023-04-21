#include "beam_model.h"

Beam::Beam(double l, double E, double A, double I, double q)
{
    m_l = l;
    m_E = E;
    m_A = A;
    m_I = I;
    m_q = q;
}

std::shared_ptr<Beam> Beam::create(double l, double E, double A, double I, double q)
{
    return std::make_shared<Beam>(l, E, A, I, q);
}

double Beam::l()
{
    return m_l;
}

double Beam::E()
{
    return m_E;
}

double Beam::A()
{
    return m_A;
}

double Beam::I()
{
    return m_I;
}

void Beam::l(double value)
{
    m_l = value;
}

void Beam::E(double value)
{
    m_E = value;
}

void Beam::A(double value)
{
    m_A = value;
}

void Beam::I(double value)
{
    m_I = value;
}

double Beam::q()
{
    return m_q;
}

void Beam::q(double value)
{
    m_q = value;
}

BeamModel::BeamModel(int nBeams)
{
    this->init_beams(nBeams);
}

void BeamModel::init_beams(int nBeams)
{
    m_beams.clear();

    for (auto i=0; i<nBeams; i++)
        m_beams.emplace_back(Beam::create());
}

std::shared_ptr<BeamModel> BeamModel::create(int nBeams)
{
    return std::make_shared<BeamModel>(nBeams);
}

void BeamModel::add(double l)
{
    m_beams.emplace_back(Beam::create(l));
}

void BeamModel::removeLast()
{
    if (m_beams.size()>1)
        m_beams.pop_back();
}

double BeamModel::length()
{
    auto l = 0.0;

    for (auto& beam : m_beams)
        l += beam->l();

    return l;
}

double BeamModel::maxLoad()
{
    auto max_q = -1e300;

    for (auto& beam : m_beams)
        if (std::abs(beam->q())>max_q)
            max_q = std::abs(beam->q());

    return max_q;
}

const std::vector<BeamPtr> &BeamModel::beams()
{
    return m_beams;
}

BeamPtr BeamModel::beam(int idx)
{
    if ((idx>=0)&&(idx<m_beams.size()))
        return m_beams[idx];
    else
        return BeamPtr();
}

int BeamModel::beam_pos_from_x(double x)
{
    auto x0 = 0.0;
    auto x1 = 0.0;
    auto i = 0;

    for (auto& beam : m_beams)
    {
        x1 = x0 + beam->l();

        if ((x>=x0)&&(x<x1))
            return i;

        i++;
        x0 = x1;
    }

    return -1;
}


