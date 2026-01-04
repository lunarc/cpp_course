#include <print>

int main()
{
    int a[] = {0, 1, 2, 3};
    int* b;
    int* c;
    int* d;
    
    b = a;
    
    std::println("a = {}", static_cast<void*>(a));
    std::println("b = {}", static_cast<void*>(b));
    std::println("a[0] = {}", a[0]);
    std::println("b[0] = {}", b[0]);
    std::println("*b = {}", *b);
    std::println("*a = {}", *a);
    
    c = &a[2];

    std::println("c = {}", static_cast<void*>(c));
    std::println("*c = {}", *c);

    d = b + 2;

    std::println("d = {}", static_cast<void*>(d));
    std::println("*d = {}", *d);
}
