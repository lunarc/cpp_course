#include <iostream>

#include "array_utils2.h"

using namespace std;

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