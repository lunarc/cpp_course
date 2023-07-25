#include <iostream>

using namespace std;

const int rows = 4;
const int cols = 8;

int main()
{
    int** array = new int*[rows];
    
    int counter = 0;
    
    for (auto i=0; i<rows; i++)
    {
        array[i] = new int[cols];
        
        for (auto j=0; j<cols; j++)
            array[i][j] = counter++;
    }
    
    for (auto i=0; i<rows; i++)
    {
        for (auto j=0; j<cols; j++)
            cout << array[i][j] << ", ";
        
        cout << endl;
    }

    // Deleting row arrays

    for (auto i=0; i<rows; i++)
        delete [] array[i];

    // Delete main array.
    
    delete [] array;
}
