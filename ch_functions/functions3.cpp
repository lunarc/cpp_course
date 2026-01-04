#include <iostream>
#include <print>

void simple(int a)
{
    std::println("The value of a = {}", a);
    std::println("&a = {}", static_cast<void*>(&a));
}

int main()
{
    int a = 42;
    simple(a);
    
    std::println("&a = {}", static_cast<void*>(&a));
}
