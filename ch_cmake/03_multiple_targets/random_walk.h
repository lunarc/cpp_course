#pragma once

#include <vector>

// Simulate n_walkers independent 1D random walks with n_steps steps and
// return the final position of each walker.
std::vector<double> random_walk(int n_walkers, int n_steps, unsigned int seed);
