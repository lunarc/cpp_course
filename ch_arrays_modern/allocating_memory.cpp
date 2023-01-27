#include <iostream>
#include <memory>

int main()
{
    std::unique_ptr<int> a = std::make_unique<int>();
    
    *a = 42;
    
    std::cout << "a.get() = " << a.get() << "\n";
    std::cout << "*a = " << *(a.get()) << "\n";
}