#include <iostream>
#include <memory>

const int rows = 4;
const int cols = 8;

void* operator new(size_t size)
{
    //void * p = ::operator new(size);
    void * p = malloc(size); 
    std::cout << "new called with size: " << size << " at " << p << "\n";
    return p;    
}

void operator delete(void * p)
{
    std::cout << "delete called for " << p << "\n";
    free(p);
}

int main()
{
    //std::unique_ptr<std::unique_ptr<int[]>[]> array = std::make_unique<std::unique_ptr<int[]>[]>(rows);
    auto array = std::make_unique<std::unique_ptr<int[]>[]>(rows);
    
    auto counter = 0;
    
    for (auto i=0; i<rows; i++)
    {
        array[i] = std::make_unique<int[]>(cols);
       
        for (auto j=0; j<cols; j++)
            array[i][j] = counter++;
    }
    
    for (auto i=0; i<rows; i++)
    {
        for (auto j=0; j<cols; j++)
            std::cout << array[i][j] << ", ";
        
        std::cout << "\n";
    }
}