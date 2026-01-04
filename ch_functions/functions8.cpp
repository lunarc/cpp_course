#include <iostream>
#include <print>

void simple(int* a)
{
    a[3] = 42;
}

int main()
{
    int a[] = { 1, 2, 3, 4 };
    simple(a);
    std::println("a[3] = {}", a[3]);
}
