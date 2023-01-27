#include <iostream>
#include <array>

int main()
{
    std::array<int, 10> a;
    
    for (int i=0; i<10; i++)
        a[i] = i;

    for (auto& v : a)
        std::cout << v << "\n";
     
    std::cout << "a.data() = " << a.data() << "\n";
    std::cout << "a[5] = " << a[5] << "\n";
}