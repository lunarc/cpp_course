#include <print>

int main()
{
    int* a = nullptr;
    int* b = nullptr;
    
    a = new int[10];
    
    for (auto i=0; i<10; i++)
        a[i] = i;
    
    b = &a[6];
    
    std::println("a = {}", static_cast<void*>(a));
    std::println("a[5] = {}", a[5]);
    std::println("b = {}", static_cast<void*>(b));
    std::println("*b = {}", *b);
    
    delete[] a;
}
