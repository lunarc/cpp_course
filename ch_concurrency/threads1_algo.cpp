#include <iostream>
#include <execution>
#include <numeric>
#include <vector>
#include <utils/print.h>

using namespace std;

int main()
{
    int a = 0;
    int b = 100000000;

    std::print("Summing from {0} to {1} using parallel algorithms\n", a, b);

    // Create a vector with the range [a, b]
    std::vector<int> numbers(b - a + 1);
    std::iota(numbers.begin(), numbers.end(), a);

    // Use parallel reduce to sum all numbers
    long long totalSum = std::reduce(
        std::execution::par,
        numbers.begin(),
        numbers.end(),
        0LL
    );

    std::print("Total sum = {0}\n", totalSum);

    long long expected = (long long)(b - a + 1) * (a + b) / 2;
    std::print("Expected sum = {0}\n", expected);
    std::print("Difference = {0}\n", totalSum - expected);

    return 0;
}
