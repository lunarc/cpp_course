#include <print>

int main()
{
    int* a = nullptr;
    
    a = new int;
    
    *a = 42;
    
    std::println("a = {}", static_cast<void*>(a));
    std::println("*a = {}", *a);
    
    delete a;
}
