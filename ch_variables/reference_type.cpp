#include <print>

int main()
{
    int a = 42;
    int& b = a;
    
    std::println("a = {}", a);
    std::println("b = {}", b);
    std::println("&a = {}", static_cast<void*>(&a));
    std::println("&b = {}", static_cast<void*>(&b));
}