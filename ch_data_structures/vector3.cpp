#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

int main()
{
    srand((unsigned)time(0));
    
    vector<int> vec;
    
    for (int i=0; i<10; i++)
        vec.emplace_back(rand());
    
    sort(vec.begin(), vec.end());
    reverse(vec.begin(), vec.end());
    
    for (auto it=vec.begin(); it!=vec.end(); it++)
        cout << *it << endl;
}