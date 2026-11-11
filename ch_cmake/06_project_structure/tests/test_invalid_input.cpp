// Constructing a solver with too few points must throw an exception.

#include <heat/heat1d.h>

#include <cstdio>
#include <print>
#include <stdexcept>

int main()
{
    try
    {
        heat::Heat1D rod(2, 1.0, 1.0);
    }
    catch (const std::invalid_argument&)
    {
        std::println("Exception thrown as expected");
        return 0;
    }

    std::println(stderr, "No exception thrown for n_points = 2");
    return 1;
}
