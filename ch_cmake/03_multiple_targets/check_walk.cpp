#include "random_walk.h"

#include <print>

int main()
{
    // With an even number of steps the final position must be even.
    auto positions = random_walk(100, 10, 1);

    for (double x : positions)
    {
        if (static_cast<int>(x) % 2 != 0)
        {
            std::println("FAILED: odd position {}", x);
            return 1;
        }
    }

    std::println("OK");
    return 0;
}
