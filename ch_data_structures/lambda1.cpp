#include <algorithm>
#include <iostream>

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
}
