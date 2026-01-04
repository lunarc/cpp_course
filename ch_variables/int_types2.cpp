#include <print>

using std::println;

int main()
{
    int a;
    unsigned int b;
    long int c;
    unsigned long int d;
    
    a = -1; b = -1;
    c = -1; d = -1;
    
    println("a = {}, sizeof(a) = {}", a, sizeof(a));
    println("b = {}, sizeof(b) = {}", b, sizeof(b));
    println("c = {}, sizeof(c) = {}", c, sizeof(c));
    println("d = {}, sizeof(d) = {}", d, sizeof(d));
}
