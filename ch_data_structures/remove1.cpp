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
    std::vector v1 = { 6, 4, 7, 3, 9, 0, 1, 5, 9 };

    auto removed_item = std::remove(v1.begin(), v1.end(), 9);

    if (removed_item != v1.end())
        v1.erase(removed_item, v1.end());

    print_vector(v1);

    removed_item = std::remove_if(v1.begin(), v1.end(), [](int v)
        { return v % 2 == 0; });

    if (removed_item != v1.end())
        v1.erase(removed_item, v1.end());

    print_vector(v1);

    std::vector v2 = { 4, 5, 7, 4, 3, 3, 7, 7, 4, 5 };
    // std::vector v2 = { 1, 2, 3, 4, 5 };

    auto last = std::unique(v2.begin(), v2.end());
    v2.erase(last, v2.end());

    std::sort(v2.begin(), v2.end());

    last = std::unique(v2.begin(), v2.end());
    v2.erase(last, v2.end());

    print_vector(v2);
}
