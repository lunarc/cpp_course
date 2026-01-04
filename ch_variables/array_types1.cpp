#include <print>

int main()
{
    int a[2];
    
    a[0] = 1;
    a[1] = 2;
    
    std::println("{}, {}", a[0], a[1]);
     
    double b[] = { 1.0, 2.0, 3.0, 4.0 };
    b[3] = 42.0;
    
    std::println("{}, {}, {}, {}", b[0], b[1], b[2], b[3]);

    int c[2][2] = { { 1, 2 }, { 3, 4 } };

    std::println("{}, {}", c[0][0], c[0][1]);
    std::println("{}, {}", c[1][0], c[1][1]);
}
