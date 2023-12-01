#include <algorithm>
#include <iostream>
#include <vector>

void print_vector(auto v)
{
    for (auto& item : v)
        std::cout << item << " ";
    std::cout << std::endl;
}

int main()
{
    std::vector<int> v1(20);

    std::fill(v1.begin(), v1.end(), 42);

    print_vector(v1);
}
