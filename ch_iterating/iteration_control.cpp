#include <iostream>
#include <print>

int main() 
{
    auto counter = 1;
    
    while (counter <= 10) 
    {
        std::println("counter = {}", counter);
        
        if (counter == 5)
        {
            counter = counter + 2;
            continue;
        }
        
        if (counter == 9)
            break;
        
        counter = counter + 1;
    }
}