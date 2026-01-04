#include <iostream>
#include <print>

void simple(int* a)
{
    *a = 43;
}

int main()
{
    int a = 42;
    
    std::println("Before function call: a = {}", a);
    simple(&a);
    std::println("After function call : a = {}", a);
}
