#pragma once

#include <Eigen/Dense>

namespace calfem
{

enum TAnalysisType {PLANE_STRESS, PLANE_STRAIN};
void removeRow(Eigen::MatrixXd &matrix, unsigned int rowToRemove);
void removeColumn(Eigen::MatrixXd &matrix, unsigned int colToRemove);
Eigen::MatrixXd hooke(TAnalysisType ptype, double E, double v);
Eigen::Matrix4d bar2e(const Eigen::Vector2d& ex, const Eigen::Vector2d& ey, const Eigen::Vector2d& ep);
double bar2s(const Eigen::Vector2d& ex, const Eigen::Vector2d& ey, const Eigen::Vector2d& ep, const Eigen::Vector4d& ed);
void assem(const Eigen::MatrixXi& topo, Eigen::MatrixXd& K, const Eigen::MatrixXd& Ke);
void solveq(const Eigen::MatrixXd& K, const Eigen::MatrixXd& f, const Eigen::VectorXi& bcDofs, const Eigen::VectorXi& bcValues, Eigen::MatrixXd& a, Eigen::MatrixXd& r);
void extractEldisp(const Eigen::MatrixXi& edof, const Eigen::MatrixXd& a, Eigen::MatrixXd& ed);

} // namespace calfem
