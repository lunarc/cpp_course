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

    std::remove()

    print_vector(v1);
}
