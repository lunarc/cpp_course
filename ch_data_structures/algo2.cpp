#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void myfunc(int i)
{
    cout << i << endl;
}

bool greaterThan5(int i)
{
    return i>5;
}

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

    for_each(vec.begin(), vec.end(), myfunc);
    
    it = find_if(vec.begin(), vec.end(), greaterThan5);
    cout << "found " << *it << endl;
    
    sort(vec.begin(), vec.end());
    
    for_each(vec.begin(), vec.end(), myfunc);
    
    cout << "max value = " << *max_element(vec.begin(), vec.end()) << endl;
    
    cout << "min value = " << *min_element(vec.begin(), vec.end()) << endl;
    
    fill(vec.begin(), vec.end(), 0);

    for_each(vec.begin(), vec.end(), myfunc);    
}