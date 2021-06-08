#include <iostream>
#include <vector>
#include <memory>

using namespace std;

const auto rows = 4;
const auto cols = 8;

int main()
{
    vector<int*> array(rows);
    unique_ptr<int[]> memory = make_unique<int[]>(rows*cols);
  
    auto counter = 0;
    
    for (auto i=0; i<rows; i++)
    {
        //array[i] = memory.get() + sizeof(int) * i * cols;
        array[i] = &memory[i*cols];

        for (int j=0; j<cols; j++)
            array[i][j] = counter++;
    }
    
    for (auto i=0; i<rows; i++)
    {
        for (auto j=0; j<cols; j++)
            cout << array[i][j] << ", ";
        
        cout << endl;
    }
}