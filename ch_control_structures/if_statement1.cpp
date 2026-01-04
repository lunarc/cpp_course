#include <print>

int main()
{
    for (int i=1; i<=10; i++)
    {
        std::println("i = {}", i);
        
        if (i==5)
            std::println("i == 5");
    }
}