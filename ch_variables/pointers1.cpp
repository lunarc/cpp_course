#include <print>

int main()
{
    int a{42};
    int* b;
    void* c;
    
    b = &a; // Assigning the address of a to pointer b
    c = b;  // Assigning the pointer b to the non-typed pointer c

    // To assign a non-typed pointer to a typed pointer we need
    // to cast the c pointer to an int* pointer

    b = static_cast<int*>(c);
    
    std::println("a = {}", a);
    std::println("b = {}", static_cast<void*>(b));
    std::println("&a = {}", static_cast<void*>(&a));
    std::println("*b = {}", *b);
    std::println("c = {}", c);
}
