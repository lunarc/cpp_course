#include <iostream>
#include <print>

int main()
{
    int number;
    
    std::print("Enter a number : ");
    
    std::cin >> number;
    
    int outValue = (number>50) ? 42 : 21;
    
    std::println("outValue = {}", outValue);
}