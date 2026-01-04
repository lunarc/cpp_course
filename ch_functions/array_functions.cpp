#include <print>

void createArray(int**& array, int rows, int cols)
{
    array = new int*[rows];
    array[0] = new int[rows*cols];    

    for (auto i=0; i<rows; i++)
        array[i] = &array[0][i*cols];
}

void zeroArray(int**& array, int rows, int cols)
{
    for (auto i=0; i<rows; i++)
        for (auto j=0; j<cols; j++)
            array[i][j] = 0;
}

void deleteArray(int**& array)
{
    delete [] array[0];
    delete [] array;
}

int main()
{
    int** array;
    
    createArray(array, 4, 8);
    zeroArray(array, 4, 8);
    
    for (auto i=0; i<4; i++)
    {
        for (auto j=0; j<8; j++)
            std::print("{}, ", array[i][j]);
        
        std::print("\n");
    }

    deleteArray(array);
}