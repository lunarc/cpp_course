#include <print>
#include <typeinfo>

int main()
{
    auto a = 42;    // By default int
    auto b = 42l;   // suffix defines a long
    auto c = 42.0;  // By default a double
    auto d = 42.0f; // suffix denotes a float

    std::println("{}", typeid(a).name());
    std::println("{}", typeid(b).name());
    std::println("{}", typeid(c).name());
    std::println("{}", typeid(d).name());
}
