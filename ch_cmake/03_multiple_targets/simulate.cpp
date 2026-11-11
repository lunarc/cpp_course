#include "random_walk.h"

#include <fstream>
#include <ostream> // std::println(std::ostream&, ...) for writing to files
#include <print>

int main()
{
    const int n_walkers = 10000;
    const int n_steps = 100;

    auto positions = random_walk(n_walkers, n_steps, 42);

    // std::println can also write to a file stream.
    std::ofstream out("positions.txt");
    for (double x : positions)
        std::println(out, "{}", x);

    std::println("Wrote {} positions to positions.txt", positions.size());
    return 0;
}
