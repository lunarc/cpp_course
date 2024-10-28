#include "beam_model.h"

#include "calfem.h"

#include <QDebug>

#include <format>

using namespace Eigen;
using namespace BeamAnalysis;

Node::Node()
{
    m_dofs[0] = 1;
    m_dofs[1] = 2;
}

std::shared_ptr<Node> Node::create()
{
    return std::make_shared<Node>();
}

int Node::enumDofs(int startDof)
{
    m_dofs[0] = startDof++;
    m_dofs[1] = startDof++;
    return startDof;
}

int Node::dof(int idx)
{
    if ((idx >= 0) && (idx < 2))
        return m_dofs[idx];
    else
        return -1;
}

void Node::setDof(int idx, int value)
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

void Beam::setNodes(NodePtr& n0, NodePtr& n1)
{
    m_node0 = n0;
    m_node1 = n1;
}

NodePtr Beam::n0()
{
    return m_node0;
}

NodePtr Beam::n1()
{
    return m_node1;
}

void Beam::setResults(Eigen::MatrixXd& es, Eigen::MatrixXd& edi, Eigen::MatrixXd& eci)
{
    m_es = es;
    m_edi = edi;
    m_eci = eci;

    m_maxM = std::max(std::abs(m_es.col(0).maxCoeff()), std::abs(m_es.col(0).minCoeff()));
    m_maxV = std::max(std::abs(m_es.col(1).maxCoeff()), std::abs(m_es.col(1).minCoeff()));
    m_maxv = std::max(std::abs(m_edi.maxCoeff()), std::abs(m_edi.minCoeff()));
}

int Beam::evalCount()
{
    return m_es.rows();
}

double Beam::M(int idx)
{
    if ((idx >= 0) && (idx < this->evalCount()))
        return m_es(idx, 0);
    else
        return 0.0;
}

double Beam::V(int idx)
{
    if ((idx >= 0) && (idx < this->evalCount()))
        return m_es(idx, 1);
    else
        return 0.0;
}

double Beam::v(int idx)
{
    if ((idx >= 0) && (idx < this->evalCount()))
        return m_edi(idx, 0);
    else
        return 0.0;
}

double Beam::x(int idx)
{
    if ((idx >= 0) && (idx < this->evalCount()))
        return m_eci(idx, 0);
    else
        return 0.0;
}

double Beam::maxM()
{
    return m_maxM;
}

double Beam::maxV()
{
    return m_maxV;
}

double Beam::maxv()
{
    return m_maxv;
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
    : m_selectedBeam { nullptr }
    , m_logger { Logger::getInstance() }
{
    m_logger.log(Logger::LogLevel::INFO, "BeamModel created");
    this->init_beams(nBeams);
}

void BeamModel::init_beams(int nBeams)
{
    m_logger.log(Logger::LogLevel::INFO, std::format("Initalising {} beams.", nBeams));
    m_beams.clear();
    m_nodes.clear();

    for (auto i = 0; i < nBeams; i++)
    {
        m_nodes.emplace_back(Node::create());
        m_beams.emplace_back(Beam::create());
    }
    m_nodes.emplace_back(Node::create());
}

std::shared_ptr<BeamModel> BeamModel::create(int nBeams)
{
    return std::make_shared<BeamModel>(nBeams);
}

void BeamModel::add(double l)
{
    m_logger.log(Logger::LogLevel::INFO, std::format("Adding beam with length {}.", l));

    m_beams.emplace_back(Beam::create(l));
    m_nodes.emplace_back(Node::create());
    this->connect();
    this->solve();
}

void BeamModel::removeLast()
{
    m_logger.log(Logger::LogLevel::INFO, "Removing last beam.");

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

    for (auto& beam : m_beams)
        l += beam->l();

    return l;
}

double BeamModel::maxLoad()
{
    auto max_q = -1e300;

    for (auto& beam : m_beams)
        if (std::abs(beam->q()) > max_q)
            max_q = std::abs(beam->q());

    return max_q;
}

double BeamModel::maxM()
{
    auto maxM = -1e300;

    for (auto& beam : m_beams)
        if (std::abs(beam->maxM()) > maxM)
            maxM = std::abs(beam->maxM());

    return maxM;
}

double BeamModel::maxV()
{
    auto maxV = -1e300;

    for (auto& beam : m_beams)
        if (std::abs(beam->maxV()) > maxV)
            maxV = std::abs(beam->maxV());

    return maxV;
}

double BeamModel::maxv()
{
    auto maxv = -1e300;

    for (auto& beam : m_beams)
        if (std::abs(beam->maxv()) > maxv)
            maxv = std::abs(beam->maxv());

    return maxv;
}

const std::vector<BeamPtr>& BeamModel::beams()
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

void BeamModel::setSelectedBeam(int idx)
{
    m_selectedBeam = this->beam(idx);
}

BeamPtr BeamModel::selectedBeam()
{
    return m_selectedBeam;
}

int BeamModel::beam_pos_from_x(double x)
{
    auto x0 = 0.0;
    auto x1 = 0.0;
    auto i = 0;

    for (auto& beam : m_beams)
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
    m_logger.log(Logger::LogLevel::INFO, "Connecting nodes and beams.");

    auto dof = 1;

    for (auto& node : m_nodes)
        dof = node->enumDofs(dof);

    auto i = 0;

    for (auto& beam : m_beams)
    {
        beam->setNodes(m_nodes[i], m_nodes[i + 1]);
        i++;
    }
}

void BeamModel::solve()
{
    m_logger.log(Logger::LogLevel::INFO, "Solving beam model.");

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

    for (auto& beam : m_beams)
    {
        ex << x, x + beam->l();
        ep << beam->E(), beam->I();
        auto eq = beam->q();
        topo << beam->n0()->dof(0) - 1, beam->n0()->dof(1) - 1, beam->n1()->dof(0) - 1, beam->n1()->dof(1) - 1;

        calfem::beam1e(ex, ep, Ke, fe, eq);
        calfem::assem(topo, K, Ke, f, fe);
    }

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

    calfem::solveq(K, f, bcDofs, bcValues, a, R);

    auto nep = 100;

    Vector4d ed;
    MatrixXd es(nep, 2);
    VectorXd edi(nep);
    VectorXd eci(nep);

    for (auto& beam : m_beams)
    {
        ex << x, x + beam->l();
        ep << beam->E(), beam->I();
        auto eq = beam->q();
        ed << a(beam->n0()->dof(0) - 1), a(beam->n0()->dof(1) - 1), a(beam->n1()->dof(0) - 1),
            a(beam->n1()->dof(1) - 1);

        MatrixXd es, edi, eci;
        calfem::beam1s(ex, ep, ed, es, edi, eci, eq, 100);

        beam->setResults(es, edi, eci);
    }
}
