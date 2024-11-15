#pragma once

#include <Eigen/Dense>

namespace calfem
{

enum TAnalysisType
{
    PLANE_STRESS,
    PLANE_STRAIN
};

Eigen::MatrixXd hooke(TAnalysisType ptype, double E, double v);

Eigen::Matrix4d bar2e(const Eigen::Vector2d &ex, const Eigen::Vector2d &ey, const Eigen::Vector2d &ep);

double bar2s(const Eigen::Vector2d &ex, const Eigen::Vector2d &ey, const Eigen::Vector2d &ep,
             const Eigen::Vector4d &ed);

void beam1e(const Eigen::Vector2d &ex, const Eigen::Vector2d &ep, Eigen::Matrix4d &Ke, Eigen::Vector4d &fe,
            double eq = 0.0);

void beam1s(const Eigen::VectorXd &ex, const Eigen::VectorXd &ep, const Eigen::VectorXd &ed, Eigen::MatrixXd &es,
            Eigen::MatrixXd &edi, Eigen::MatrixXd &eci, double eq, int nep = 2);

void assem(const Eigen::VectorXi &topo, Eigen::MatrixXd &K, const Eigen::MatrixXd &Ke, Eigen::MatrixXd &f,
           const Eigen::MatrixXd &fe);

void solveq(const Eigen::MatrixXd &K, const Eigen::MatrixXd &f, const Eigen::VectorXi &bcDofs,
            const Eigen::VectorXd &bcValues, Eigen::MatrixXd &a, Eigen::MatrixXd &r);

void extractEldisp(const Eigen::MatrixXi &edof, const Eigen::MatrixXd &a, Eigen::MatrixXd &ed);

} // namespace calfem
