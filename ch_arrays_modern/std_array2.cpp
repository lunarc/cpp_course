#include <iostream>
#include <array>

using namespace std;

const int rows = 4;
const int cols = 8;

int main()
{
    array<array<int, cols>, rows> a;
    
    for (auto i=0; i<rows; i++)
        for (auto j=0; j<cols; j++)
            a[i][j] = i*j;

    for (auto row : a)
    {
        for (auto col : row)
            cout << col << ", ";
        
        cout << endl;
    }
     
}