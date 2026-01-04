#include <print>

int main() 
{
    int counter = 1;
    
    do
    {
        std::println("counter = {}", counter);
        counter = counter + 1;
    }
    while (counter<=10);
}