#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand((unsigned)time(0));
    
    vector<int> vec;
    
    for (int i=0; i<10; i++)
        vec.push_back(rand());

    for (size_t i=0; i<vec.size(); i++)
        cout << vec[i] << endl;
}