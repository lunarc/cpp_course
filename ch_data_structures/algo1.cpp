#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> vec;
    vector<int>::iterator it;
    
    vec.push_back(5);
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(4);
    vec.push_back(8);

    it = find(vec.begin(), vec.end(), 4);
    
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