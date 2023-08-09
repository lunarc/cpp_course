#include <iostream>
#include <array>

const int rows = 4;
const int cols = 8;

int main()
{
    std::array<std::array<int, cols>, rows> arr;
    
    for (auto i=0; i<rows; i++)
        for (auto j=0; j<cols; j++)
            arr[i][j] = i * j;

    for (auto& row : arr)
    {
        for (auto value : row)
            std::cout << value << ", ";
        
        std::cout << "\n";
    }
     
}