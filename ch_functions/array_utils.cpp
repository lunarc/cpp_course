#include "array_utils.h"

int** createArray(int rows, int cols)
{
    int** array = new int*[rows];
    array[0] = new int[rows*cols];
    
    for (auto i=0; i<rows; i++)
        array[i] = &array[0][i*cols];
    
    return array;
}

void zeroArray(int**& array, int rows, int cols)
{
    for (auto i=0; i<rows; i++)
        for (auto j=0; j<cols; j++)
            array[i][j] = 0;
}

void deleteArray(int**& array)
{
    delete array[0];
    delete array;
}
