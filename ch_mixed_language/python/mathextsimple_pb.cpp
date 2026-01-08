#include <pybind11/pybind11.h>

long long factorial(int n) 
{
    if (n < 0) 
    {
        throw std::invalid_argument("Factorial requires non-negative integer");
    }

    long long result = 1;
    for (int i = 2; i <= n; i++) 
    {
        result *= i;
        
        // Check for overflow

        if (result < 0) 
        {
            throw std::overflow_error("Factorial result too large");
            return NULL;
        }
    }

    return result;
}

PYBIND11_MODULE(mathextsimple_pb, m) {
    m.def("factorial", &factorial, "Calculate factorial of n");
}