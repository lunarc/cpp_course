#include <print>

int main()
{
    auto sum = 0;
    
    for (auto i=0; i<=10000; sum += ++i);
    
    std::println("sum = {}", sum);
}
