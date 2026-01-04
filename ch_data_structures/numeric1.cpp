#include <algorithm>
#include <print>
#include <numeric>
#include <vector>

void print_vector(auto v)
{
    for (auto& item : v)
        std::print("{} ", item);
    std::println("");
}

int main()
{
    std::vector<double> v1(20);

    std::iota(v1.begin(), v1.end(), 1.0);

    print_vector(v1);

    auto sum = std::accumulate(v1.begin(), v1.end(), 0.0);

    std::println("sum = {}", sum);

    auto prod = std::accumulate(v1.begin(), v1.end(), 1.0, std::multiplies<double>());

    std::println("prod = {}", prod);
}
