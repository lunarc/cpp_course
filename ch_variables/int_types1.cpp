#include <print>

int main()
{
    int a;
    unsigned int b;
    long int c;
    unsigned long int d;

    a = -1;
    b = -1; // What happens here?
    c = -1;
    d = -1; // and here?

    std::println("a = {}", a);
    std::println("b = {}", b);
    std::println("c = {}", c);
    std::println("d = {}", d);
}
