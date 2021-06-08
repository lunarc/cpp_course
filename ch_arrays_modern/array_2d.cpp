#include <iostream>
#include <memory>

using namespace std;

const int rows = 4;
const int cols = 8;

void* operator new(size_t size)
{
    //void * p = ::operator new(size);
    void * p = malloc(size); 
    cout << "new called with size: " << size << " at " << p << endl;
    return p;    
}

void operator delete(void * p)
{
    cout << "delete called for " << p << endl;
    free(p);
}

int main()
{
    unique_ptr<unique_ptr<int[]>[]> array = make_unique<unique_ptr<int[]>[]>(rows);
    
    auto counter = 0;
    
    for (auto i=0; i<rows; i++)
    {
        array[i] = make_unique<int[]>(cols);
       
        for (auto j=0; j<cols; j++)
            array[i][j] = counter++;
    }
    
    for (auto i=0; i<rows; i++)
    {
        for (auto j=0; j<cols; j++)
            cout << array[i][j] << ", ";
        
        cout << endl;
    }
}