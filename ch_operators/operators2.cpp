#include <print>

int main()
{
    int a, b, c;
    
    a = 42;
    
    b = ++a;
    c = a++;
    
    std::println("b = {}", b);
    std::println("c = {}", c);
}