#include <iostream>

using namespace std;

int** createArray(int rows, int cols)
{
    int** array = new int*[rows];
    array[0] = new int[rows*cols];    

    for (int i=0; i<rows; i++)
        array[i] = &array[0][i*cols];
    
    return array;
}

void zeroArray(int**& array, int rows, int cols)
{
    for (int i=0; i<rows; i++)
        for (int j=0; j<cols; j++)
            array[i][j] = 0;
}

void deleteArray(int**& array)
{
    delete array[0];
    delete array;
}

int main()
{
    int** array;
    
    array = createArray(4, 8);
    zeroArray(array, 4, 8);
    
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<8; j++)
            cout << array[i][j] << ", ";
        
        cout << endl;
    }

    deleteArray(array);
}