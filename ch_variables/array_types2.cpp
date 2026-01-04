#include <print>

int main()
{
    int a[] = {1,2,3,4};
    int* b;
    
    a[3] = 42;
    
    std::println("{}, {}, {}, {}", a[0], a[1], a[2], a[3]);
    
    b = a;

    std::println("{}, {}, {}, {}", b[0], b[1], b[2], b[3]);
}
