#include "random_walk.h"

#include <random>

std::vector<double> random_walk(int n_walkers, int n_steps, unsigned int seed)
{
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> coin(0, 1);

    std::vector<double> positions(n_walkers, 0.0);

    for (auto& x : positions)
        for (int step = 0; step < n_steps; ++step)
            x += coin(rng) == 0 ? -1.0 : 1.0;

    return positions;
}
