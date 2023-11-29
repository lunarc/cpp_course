#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <cmath>


void tabulate(double x_start, double x_end, double dx, std::function<double(double x)> const& f)
{
    auto x = x_start;

    std::cout << "x, f(x)" << std::endl;
    std::cout << "-------------------" << std::endl;

    while (x <= x_end)
    {
        std::cout << x << ", " << f(x) << std::endl;
        x += dx;
    }
}


void print_vector(auto v)
{
    for (auto& item : v)
        std::cout << item << " ";
    std::cout << std::endl;
}

double q(double x)
{
    return cos(x);
}

int main()
{
    int c = 42;

    auto f = [](int x) { return x * x; };
    std::cout << f(5) << std::endl;

    auto g = [=](int x) { return x * x + c; };
    std::cout << g(5) << std::endl;

    auto h = [&](int x) { return x * x + c; };
    std::cout << h(5) << std::endl;

    auto p = [&c](int x) -> int { return x * x + c; };
    std::cout << p(5) << std::endl;

    std::vector v1 = { 6, 4, 7, 3, 9, 0, 1, 5 };
    std::vector v2 = { 6, 4, 7, 3, 9, 0, 1, 5 };

    auto greater_func = [](int a, int b) -> bool { return a > b; };

    std::sort(v1.begin(), v1.end(), greater_func);
    std::sort(v2.begin(), v2.end(), [](int a, int b) -> bool { return a < b; });

    print_vector(v1);
    print_vector(v2);

    tabulate(-6.0, 6.0, 0.2, [](double x) -> double { return sin(x); });
    tabulate(-6.0, 6.0, 0.2, q);

    if (std::all_of(v1.begin(), v1.end(), [](int i) { return i < 10; }))
        std::cout << "All values of v1 are less than 10." << std::endl;

    if (std::any_of(v1.begin(), v1.end(), [](int i) { return i % 2 == 0; }))
        std::cout << "Some of the values are even." << std::endl;

    if (std::none_of(v1.begin(), v1.end(), [](int i) { return i < 0; }))
        std::cout << "No numbers are less than zero." << std::endl;

    if (std::ranges::all_of(v1, [](int i) { return i < 10; }))
        std::cout << "All values of v1 are less than 10. (ranges)" << std::endl;

    if (std::ranges::any_of(v1, [](int i) { return i % 2 == 0; }))
        std::cout << "Some of the values are even. (ranges)" << std::endl;

    if (std::ranges::none_of(v1, [](int i) { return i < 0; }))
        std::cout << "No numbers are less than zero. (ranges)" << std::endl;

    std::for_each(v1.begin(), v1.end(), [](int i) { std::cout << i << " "; });
    std::cout << std::endl;

    std::ranges::for_each(v1, [](int i) { std::cout << i << " "; });
    std::cout << std::endl;

    std::for_each(v1.begin(), v1.end(), [](int& n) { n++; });
    print_vector(v1);

    std::ranges::for_each(v1, [](int& n) { n++; });
    print_vector(v1);

    auto sum = 0;

    std::for_each(v1.begin(), v1.end(), [&sum](int n) { sum += n; });
    std::cout << "Them sum is " << sum << std::endl;

    sum = 0;

    std::ranges::for_each(v1, [&sum](int n) { sum += n; });
    std::cout << "Them sum is " << sum << std::endl;

    print_vector(v2);

    auto number_of_values = std::count(v2.begin(), v2.end(), 5);
    std::cout << number_of_values << " items with the value 5 in v2. " << std::endl;

    number_of_values = std::ranges::count(v2, 5);
    std::cout << number_of_values << " items with the value 5 in v2. " << std::endl;

    auto even_numbers = std::count_if(v2.begin(), v2.end(), [](int i) {return i % 2 == 0; });
    std::cout << even_numbers << " even numbers in v2." << std::endl;

    even_numbers = std::ranges::count_if(v2, [](int i) {return i % 2 == 0; });
    std::cout << even_numbers << " even numbers in v2 (ranges)." << std::endl;
}
