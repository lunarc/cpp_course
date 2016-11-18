#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<double> vec;

    for (int i=0; i<10; i++)
        vec.push_back(i);

    for (int i=0; i<10; i++)
        cout << vec[i] << endl;
}
