#pragma once

// Declaration of the Fortran routine in tridiag.f90. extern "C" turns
// off C++ name mangling so the linker finds the symbol
// "solve_tridiagonal" produced by bind(C, name="solve_tridiagonal").
// Fortran arrays are passed as pointers to their first element.
extern "C" void solve_tridiagonal(int n, const double* a, const double* b, const double* c,
                                  const double* d, double* x);
