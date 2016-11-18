#pragma once

#include <armadillo>

enum TAnalysisType {PLANE_STRESS, PLANE_STRAIN};

arma::mat hooke(TAnalysisType ptype, double E, double v);
arma::mat bar2e(arma::rowvec ex, arma::rowvec ey, arma::rowvec ep);
double bar2s(arma::rowvec ex, arma::rowvec ey, arma::rowvec ep, arma::rowvec ed);
void assem(arma::imat topo, arma::mat& K, arma::mat& Ke);
void solveq(arma::mat& K, arma::mat&f, arma::irowvec& bcDofs, arma::rowvec& bcValues, arma::mat& a, arma::mat& r);
void extractEldisp(arma::imat& edof, arma::mat& a, arma::mat& ed);
