#include <iostream>

using namespace std;

const int rows = 4;
const int cols = 8;

int main()
{
    int** array = new int*[rows];
    array[0] = new int[rows*cols];
    
    int counter = 0;
    
    for (int i=0; i<rows; i++)
    {
        array[i] = &array[0][i*cols];
        
        for (int j=0; j<cols; j++)
            array[i][j] = counter++;
    }
    
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
            cout << array[i][j] << ", ";
        
        cout << endl;
    }

    delete array[0];
    delete array;
}