#include <algorithm>
#include <print>
#include <vector>
#include <functional>


void print_vector(auto v)
{
    for (auto& item : v)
        std::print("{} ", item);
    std::println("");
}

int main()
{
    std::vector v = { 6, 4, 7, 3, 9, 0, 1, 5 };

    std::for_each(v.begin(), v.end(), [](int i) { std::print("{} ", i); });
    std::println("");

    std::ranges::for_each(v, [](int i) { std::print("{} ", i); });
    std::println("");

    std::for_each(v.begin(), v.end(), [](int& n) { n++; });
    print_vector(v);

    std::ranges::for_each(v, [](int& n) { n++; });
    print_vector(v);

    auto sum = 0;

    std::for_each(v.begin(), v.end(), [&sum](int n) { sum += n; });
    std::println("Them sum is {}", sum);

    sum = 0;

    std::ranges::for_each(v, [&sum](int n) { sum += n; });
    std::println("Them sum is {}", sum);

    print_vector(v);

}
