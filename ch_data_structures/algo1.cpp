#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> vec = {5, 1, 3, 4, 4, 8};
    
    auto it = find(vec.begin(), vec.end(), 4);
    
    if (it!=vec.end())
        cout << "found " << *it << endl;
    else
        cout << "Value not found." << endl;

    it = find(++it, vec.end(), 4);

    if (it!=vec.end())
        cout << "found " << *it << endl;
    else
        cout << "Value not found." << endl;

    it = find(++it, vec.end(), 4);
    
    if (it!=vec.end())
        cout << "found " << *it << endl;
    else
        cout << "Value not found." << endl;

}