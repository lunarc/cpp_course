#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <Eigen/Dense>

class BeamNode
{
  private:
    int m_dofs[2];

  public:
    BeamNode();

    static std::shared_ptr<BeamNode> create();

    int enumDofs(int startDof = 1);

    int dof(int idx);
    void setDof(int idx, int value);
};

typedef std::shared_ptr<BeamNode> BeamNodePtr;

class Beam
{
  private:
    double m_l;
    double m_E;
    double m_A;
    double m_I;
    double m_q;

    BeamNodePtr m_node0;
    BeamNodePtr m_node1;

    Eigen::MatrixXd m_es;
    Eigen::MatrixXd m_edi;
    Eigen::MatrixXd m_eci;

    double m_maxM;
    double m_maxV;
    double m_maxv;

  public:
    Beam(double l = 1.0, double E = 2.1e9, double A = 0.01, double I = 8.33e-6, double q = -1.0e3);

    static std::shared_ptr<Beam> create(double l = 1.0, double E = 2.1e9, double A = 0.01, double I = 8.33e-6,
                                        double q = -1.0e3);

    void setNodes(BeamNodePtr &n0, BeamNodePtr &n1);
    BeamNodePtr n0();
    BeamNodePtr n1();

    void setResults(Eigen::MatrixXd &es, Eigen::MatrixXd &edi, Eigen::MatrixXd &eci);

    int evalCount();
    double M(int idx);
    double V(int idx);
    double v(int idx);
    double x(int idx);

    double maxM();
    double maxV();
    double maxv();

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

class BeamModel
{
  private:
    std::vector<BeamPtr> m_beams;
    std::vector<BeamNodePtr> m_nodes;

    void init_beams(int nBeams);

  public:
    BeamModel(int nBeams);

    static std::shared_ptr<BeamModel> create(int nBeams);

    void add(double l = 1.0);
    void removeLast();

    double length();
    double maxLoad();
    double maxM();
    double maxV();
    double maxv();

    const std::vector<BeamPtr> &beams();

    BeamPtr beam(int idx);

    int beam_pos_from_x(double x);

    void connect();

    void solve();
};

typedef std::shared_ptr<BeamModel> BeamModelPtr;
