#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

void print_vector(auto v)
{
    for (auto& item : v)
        std::cout << item << " ";
    std::cout << std::endl;
}

int main()
{
    std::vector<double> v1(20);

    std::iota(v1.begin(), v1.end(), 1.0);

    print_vector(v1);

    auto sum = std::accumulate(v1.begin(), v1.end(), 0.0);

    std::cout << "sum = " << sum << "\n";

    auto prod = std::accumulate(v1.begin(), v1.end(), 1.0, std::multiplies<double>());

    std::cout << "prod = " << prod << "\n";
}
