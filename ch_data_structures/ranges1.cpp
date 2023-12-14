#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>


void print_vector(auto v)
{
    for (auto& item : v)
        std::cout << item << " ";
    std::cout << std::endl;
}

int main()
{
    std::vector v = { 6, 4, 7, 3, 9, 0, 1, 5 };

    std::for_each(v.begin(), v.end(), [](int i) { std::cout << i << " "; });
    std::cout << std::endl;

    std::ranges::for_each(v, [](int i) { std::cout << i << " "; });
    std::cout << std::endl;

    std::for_each(v.begin(), v.end(), [](int& n) { n++; });
    print_vector(v);

    std::ranges::for_each(v, [](int& n) { n++; });
    print_vector(v);

    auto sum = 0;

    std::for_each(v.begin(), v.end(), [&sum](int n) { sum += n; });
    std::cout << "Them sum is " << sum << std::endl;

    sum = 0;

    std::ranges::for_each(v, [&sum](int n) { sum += n; });
    std::cout << "Them sum is " << sum << std::endl;

    print_vector(v);

}
