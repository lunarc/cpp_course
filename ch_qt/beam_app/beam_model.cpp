#include "beam_model.h"

#include "calfem_eig.h"

#include <QDebug>

using namespace Eigen;

BeamNode::BeamNode()
{
    m_dofs[0] = 1;
    m_dofs[1] = 2;
}

std::shared_ptr<BeamNode> BeamNode::create()
{
    return std::make_shared<BeamNode>();
}

int BeamNode::enumDofs(int startDof)
{
    m_dofs[0] = startDof++;
    m_dofs[1] = startDof++;
    return startDof;
}

int BeamNode::dof(int idx)
{
    if ((idx >= 0) && (idx < 2))
        return m_dofs[idx];
    else
        return -1;
}

void BeamNode::setDof(int idx, int value)
{
    if ((idx >= 0) && (idx < 2))
        m_dofs[idx] = value;
}

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

void Beam::setNodes(BeamNodePtr &n0, BeamNodePtr &n1)
{
    m_node0 = n0;
    m_node1 = n1;
}

BeamNodePtr Beam::n0()
{
    return m_node0;
}

BeamNodePtr Beam::n1()
{
    return m_node1;
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
    m_nodes.clear();

    for (auto i = 0; i < nBeams; i++)
    {
        m_nodes.emplace_back(BeamNode::create());
        m_beams.emplace_back(Beam::create());
    }
    m_nodes.emplace_back(BeamNode::create());
}

std::shared_ptr<BeamModel> BeamModel::create(int nBeams)
{
    return std::make_shared<BeamModel>(nBeams);
}

void BeamModel::add(double l)
{
    m_beams.emplace_back(Beam::create(l));
    m_nodes.emplace_back(BeamNode::create());
    this->connect();
    this->solve();
}

void BeamModel::removeLast()
{
    if (m_beams.size() > 1)
    {
        m_beams.pop_back();
        m_nodes.pop_back();
    }
    this->connect();
    this->solve();
}

double BeamModel::length()
{
    auto l = 0.0;

    for (auto &beam : m_beams)
        l += beam->l();

    return l;
}

double BeamModel::maxLoad()
{
    auto max_q = -1e300;

    for (auto &beam : m_beams)
        if (std::abs(beam->q()) > max_q)
            max_q = std::abs(beam->q());

    return max_q;
}

const std::vector<BeamPtr> &BeamModel::beams()
{
    return m_beams;
}

BeamPtr BeamModel::beam(int idx)
{
    if ((idx >= 0) && (idx < m_beams.size()))
        return m_beams[idx];
    else
        return BeamPtr();
}

int BeamModel::beam_pos_from_x(double x)
{
    auto x0 = 0.0;
    auto x1 = 0.0;
    auto i = 0;

    for (auto &beam : m_beams)
    {
        x1 = x0 + beam->l();

        if ((x >= x0) && (x < x1))
            return i;

        i++;
        x0 = x1;
    }

    return -1;
}

void BeamModel::connect()
{
    auto dof = 1;

    for (auto &node : m_nodes)
        dof = node->enumDofs(dof);

    auto i = 0;

    for (auto &beam : m_beams)
    {
        beam->setNodes(m_nodes[i], m_nodes[i + 1]);
        qDebug() << "Beam " << i << ": " << beam->n0()->dof(0) << ", " << beam->n0()->dof(1) << " --- "
                 << beam->n1()->dof(0) << ", " << beam->n1()->dof(1);
        i++;
    }
}

void BeamModel::solve()
{
    // | )     | )     | )     | )
    // o ----- o ----- o ----- o

    auto nDofs = (m_beams.size() + 1) * 2;

    MatrixXd K(nDofs, nDofs);
    K = MatrixXd::Zero(nDofs, nDofs);

    MatrixXd f(nDofs, 1);
    f = MatrixXd::Zero(nDofs, 1);

    Matrix4d Ke;
    Vector4d fe;
    Vector2d ex;
    Vector2d ep;
    Vector4i topo;

    auto x = 0.0;

    for (auto &beam : m_beams)
    {
        ex << x, x + beam->l();
        ep << beam->E(), beam->I();
        auto eq = beam->q();
        topo << beam->n0()->dof(0) - 1, beam->n0()->dof(1) - 1, beam->n1()->dof(0) - 1, beam->n1()->dof(1) - 1;

        beam1e(ex, ep, Ke, fe, eq);
        assem(topo, K, Ke, f, fe);
    }

    // | )     | )     | )     | )
    // o ----- o ----- o ----- o

    auto nBcDofs = m_beams.size() + 1;

    VectorXi bcDofs(nBcDofs);
    bcDofs = VectorXi::Zero(nBcDofs);

    VectorXd bcValues(nBcDofs);
    bcValues = VectorXd::Zero(nBcDofs);

    auto dof = 0;

    for (auto i = 0; i < nBcDofs; i++)
    {
        bcDofs(i) = dof;
        dof += 2;
    }

    MatrixXd a(nDofs, 1);
    a = MatrixXd::Zero(nDofs, 1);

    MatrixXd R(nDofs, 1);
    R = MatrixXd::Zero(nDofs, 1);

    solveq(K, f, bcDofs, bcValues, a, R);

    for (auto i = 0; i < nDofs; i++)
        std::cout << a(i) << "\n";

    std::cout << std::endl;

    auto nep = 100;

    Vector4d ed;
    MatrixXd es(nep, 2);
    VectorXd edi(nep);
    VectorXd eci(nep);

    for (auto &beam : m_beams)
    {
        ex << x, x + beam->l();
        ep << beam->E(), beam->I();
        auto eq = beam->q();
        ed << a(beam->n0()->dof(0) - 1), a(beam->n0()->dof(1) - 1), a(beam->n1()->dof(0) - 1),
            a(beam->n1()->dof(1) - 1);

        beam1s(ex, ep, ed, eq, nep, es, edi, eci);
    }
}
