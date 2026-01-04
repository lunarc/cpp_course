#include <algorithm>
#include <print>

int main()
{
    int c = 42;

    auto f = [](int x) { return x * x; };
    std::println("{}", f(5));

    auto g = [=](int x) { return x * x + c; };
    std::println("{}", g(5));

    auto h = [&](int x) { return x * x + c; };
    std::println("{}", h(5));

    auto p = [&c](int x) -> int { return x * x + c; };
    std::println("{}", p(5));
}
