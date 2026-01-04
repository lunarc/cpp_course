#include <print>

int main()
{
    for (int i=1; i<=10; i++)
    {
        std::print("i = {}: ", i);
        
        if (i==5)
            std::println("i == 5");
        else if ( (i>=2)&&(i<=3) )
            std::println("2 <= i <= 3");
        else
            std::println("-");
    }
}