#include "calfem.h"

#include <cmath>
#include <set>

using namespace Eigen;
using namespace std;

// https://stackoverflow.com/questions/13290395/how-to-remove-a-certain-row-or-column-while-using-eigen-library-c

namespace calfem
{

void removeRow(MatrixXd &matrix, unsigned int rowToRemove)
{
    Index numRows = matrix.rows() - 1;
    Index numCols = matrix.cols();

    if (rowToRemove < numRows)
        matrix.block(rowToRemove, 0, numRows - rowToRemove, numCols) = matrix.bottomRows(numRows - rowToRemove);

    matrix.conservativeResize(numRows, numCols);
}

void removeColumn(MatrixXd &matrix, unsigned int colToRemove)
{
    Index numRows = matrix.rows();
    Index numCols = matrix.cols() - 1;

    if (colToRemove < numCols)
        matrix.block(0, colToRemove, numRows, numCols - colToRemove) = matrix.rightCols(numCols - colToRemove);

    matrix.conservativeResize(numRows, numCols);
}

MatrixXd hooke(TAnalysisType ptype, double E, double v)
{
    MatrixXd D;
    switch (ptype)
    {
    case PLANE_STRESS:
        D.resize(3, 3);
        D << 1.0, v, 0.0, v, 1.0, 0.0, 0.0, 0.0, (1.0 - v) * 0.5;
        break;
    case PLANE_STRAIN:
        D.resize(4, 4);
        D << 1.0 - v, v, v, 0.0, v, 1.0 - v, v, 0.0, v, v, 1.0 - v, 0.0, 0.0, 0.0, 0.0, 0.5 * (1.0 - 2 * v);
        break;
    default:
        break;
    }
    return D;
}

Matrix4d bar2e(const Vector2d &ex, const Vector2d &ey, const Vector2d &ep)
{
    double E = ep(0);
    double A = ep(1);
    double L = sqrt(pow(ex(1) - ex(0), 2) + pow(ey(1) - ey(0), 2));
    double C = E * A / L;

    Matrix2d Ke_loc(2, 2);

    Ke_loc << C, -C, -C, C;

    double nxx = (ex(1) - ex(0)) / L;
    double nyx = (ey(1) - ey(0)) / L;

    MatrixXd G(2, 4);

    G << nxx, nyx, 0.0, 0.0, 0.0, 0.0, nxx, nyx;

    Matrix4d Ke = G.transpose() * Ke_loc * G;
    return Ke;
}

double bar2s(const Vector2d &ex, const Vector2d &ey, const Vector2d &ep, const Vector4d &ed)
{
    double E = ep(0);
    double A = ep(1);
    double L = sqrt(pow(ex(1) - ex(0), 2) + pow(ey(1) - ey(0), 2));
    double C = E * A / L;

    double nxx = (ex(1) - ex(0)) / L;
    double nyx = (ey(1) - ey(0)) / L;

    MatrixXd G(2, 4);

    G << nxx, nyx, 0.0, 0.0, 0.0, 0.0, nxx, nyx;

    MatrixXd temp(1, 2);
    temp << -C, C;
    MatrixXd edm(4, 1);
    edm.col(0) = ed;

    // [1 x 2] x [2 x 4] x [4 x 1]

    return (temp * G * edm)(0, 0);
}

void assem(const VectorXi &topo, MatrixXd &K, const MatrixXd &Ke, MatrixXd &f, const MatrixXd &fe)
{
    for (int row = 0; row < Ke.rows(); row++)
        for (int col = 0; col < Ke.cols(); col++)
            K(topo(row), topo(col)) += Ke(row, col);

    for (int row = 0; row < fe.rows(); row++)
        f(topo(row)) += fe(row);
}

void solveq(const MatrixXd &K, const MatrixXd &f, const VectorXi &bcDofs, const VectorXd &bcValues, MatrixXd &a,
            MatrixXd &r)
{
    set<int> bc;

    for (int i = 0; i < bcDofs.size(); i++)
        bc.insert(bcDofs(i));

    VectorXi allIndices(K.rows() - bc.size());

    int count = 0;

    for (int i = 0; i < K.rows(); i++)
        if (bc.find(i) == bc.end())
            allIndices(count++) = i;

    MatrixXd Ksolve(count, count);
    VectorXd fsolve(count);

    for (int i = 0; i < count; i++)
        for (int j = 0; j < count; j++)
        {
            Ksolve(i, j) = K(allIndices(i), allIndices(j));
            fsolve(i) = f(allIndices(i), 0);
        }

    MatrixXd asolve = Ksolve.ldlt().solve(fsolve);

    for (int i = 0; i < count; i++)
        a(allIndices(i), 0) = asolve(i);

    /* Q=K*asmatrix(a)-f */

    r = K * a - f;
}

void extractEldisp(const MatrixXi &edof, const MatrixXd &a, MatrixXd &ed)
{
    Index nDofs = edof.cols();
    Index nElements = edof.rows();

    ed.resize(nElements, nDofs);

    for (int i = 0; i < nElements; i++)
        for (int j = 0; j < nDofs; j++)
            ed(i, j) = a(edof(i, j), 0);
}

void beam1e(const Eigen::Vector2d &ex, const Eigen::Vector2d &ep, Eigen::Matrix4d &Ke, Eigen::Vector4d &fe, double eq)
{
    auto E = ep(0);
    auto I = ep(1);
    auto DEI = E * I;

    auto qy = eq;
    auto x1 = ex(0);
    auto x2 = ex(1);
    auto dx = x2 - x1;
    auto L = std::abs(dx);

    Ke = Matrix4d::Zero();

    Ke << 2, 6 * L, -12, 6 * L, 6 * L, 4 * L * L, -6 * L, 2 * L * L, -12, -6 * L, 12, -6 * L, 6 * L, 2 * L * L, -6 * L,
        4 * L * L;

    Ke = Ke * DEI / std::pow(L, 3);
    fe << qy * L / 2, qy * L * L / 12, qy * L / 2, -qy * L * L / 12;
}

void beam1s(const Eigen::VectorXd &ex, const Eigen::VectorXd &ep, const Eigen::VectorXd &ed, Eigen::MatrixXd &es,
            Eigen::MatrixXd &edi, Eigen::MatrixXd &eci, double eq, int nep)
{
    double E = ep(0);
    double I = ep(1);
    double DEI = E * I;

    double qY = 0.0;

    qY = eq;

    int ne = 2;
    if (nep != -1)
        ne = nep;

    double x1 = ex(0);
    double x2 = ex(1);
    double dx = x2 - x1;
    double L = std::abs(dx);

    Eigen::VectorXd a2 = ed;

    Eigen::MatrixXd C2(4, 4);
    C2 << 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, -3.0 / (L * L), -2.0 / L, 3.0 / (L * L), -1.0 / L, 2.0 / (L * L * L),
        1.0 / (L * L), -2.0 / (L * L * L), 1.0 / (L * L);

    Eigen::VectorXd C2a = C2 * a2;

    int numPoints = ne;
    Eigen::VectorXd X = Eigen::VectorXd::LinSpaced(numPoints, 0.0, L);
    Eigen::VectorXd zero = Eigen::VectorXd::Zero(numPoints);
    Eigen::VectorXd one = Eigen::VectorXd::Ones(numPoints);

    Eigen::MatrixXd v(numPoints, 4);
    v << one, X, X.array().pow(2), X.array().pow(3);
    v = v * C2a;

    Eigen::MatrixXd d2v(numPoints, 4);
    d2v << zero, zero, 2 * one, 6 * X;
    d2v = d2v * C2a;

    Eigen::MatrixXd d3v(numPoints, 4);
    d3v << zero, zero, zero, 6 * one;
    d3v = d3v * C2a;

    if (DEI != 0.0)
    {
        v = (v.array() + (X.array().pow(4) - 2 * L * X.array().pow(3) + L * L * X.array().pow(2)) * qY / (24 * DEI))
                .matrix();
        d2v =
            (d2v.array() + (6 * X.array().pow(2) - 6 * L * X.array() + L * L * one.array()) * qY / (12 * DEI)).matrix();
        d3v = (d3v.array() + (2 * X.array() - L * one.array()) * qY / (2 * DEI)).matrix();
    }

    Eigen::MatrixXd M = DEI * d2v;
    Eigen::MatrixXd V = -DEI * d3v;

    es.resize(numPoints, 2);
    es << M, V;

    if (nep == -1)
        return;

    edi = v;
    eci = X;
}

} // namespace calfem
