#include <iostream>

using namespace std;

const int rows = 4;
const int cols = 8;

int main()
{
    int** array = new int*[rows];
    
    int counter = 0;
    
    for (int i=0; i<rows; i++)
    {
        array[i] = new int[cols];
        
        for (int j=0; j<cols; j++)
            array[i][j] = counter++;
    }
    
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
            cout << array[i][j] << ", ";
        
        cout << endl;
    }
    
    delete [] array;
}