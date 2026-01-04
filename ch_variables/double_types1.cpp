#include <print>
#include <cmath>

int main()
{
	double pi = 4 * std::atan(1);
	
    float f;
    double d;
    long double ld;
    
    f = pi;
    d = pi;
    ld = pi;
    
    std::println("f = {:.15}", f);
    std::println("d = {:.15}", d);
    std::println("ld = {:.15}", ld);
}
