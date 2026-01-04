#include <print>
#include <typeinfo>

int main()
{
    for (auto i=99999999; i<100000000; i++)
        std::println("{}, {}", i, typeid(i).name());
}
