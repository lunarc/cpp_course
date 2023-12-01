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
    std::vector v1 = { 6, 4, 7, 3, 9, 0, 1, 5 };
    std::vector v2 = { 6, 4, 7, 3, 9, 0, 1, 5 };

    auto greater_func = [](int a, int b) -> bool { return a > b; };

    std::sort(v1.begin(), v1.end(), greater_func);
    std::sort(v2.begin(), v2.end(), [](int a, int b) -> bool { return a < b; });

    print_vector(v1);
    print_vector(v2);
}
