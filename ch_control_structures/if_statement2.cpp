#include <iostream>
#include <print>

int main()
{
    for (int i=1; i<=10; i++)
    {
        if (i==5)
            std::println("i == 5");
        else
            std::println("i != 5");
    }
}