#include <print>

void simple(int* a)
{
    std::println("The value of a = {}", static_cast<void*>(a));
    std::println("*a = {}", *a);
}

int main()
{
    int a = 42;
    simple(&a);
}
