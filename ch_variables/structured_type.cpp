#include <print>

int main()
{
    struct coord3D {
        double x{};
        double y{};
    };
    
    coord3D c1;
    coord3D c2;
    
    c1.x = 0.0;
    c1.y = 0.0;
    c2.x = 1.0;
    c2.y = 1.0;
    
    std::println("c1.x = {}, c1.y = {}", c1.x, c1.y);
    std::println("c2.x = {}, c2.y = {}", c2.x, c2.y);
    std::println("sizeof(c1) = {}", sizeof(c1));
}