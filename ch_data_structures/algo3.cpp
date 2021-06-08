#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> vec = { 5, 1, 3, 4, 4, 8};
    
    for_each(vec.begin(), vec.end(), [](int i){cout << i << endl;} );
    
    auto it = find_if(vec.begin(), vec.end(), [](int i){return i>5;} );
    
    cout << "found " << *it << endl;
    
    sort(vec.begin(), vec.end());
    
    for_each(vec.begin(), vec.end(), [](int i){cout << i << endl;});
    
    cout << "max value = " << *max_element(vec.begin(), vec.end()) << endl;
    
    cout << "min value = " << *min_element(vec.begin(), vec.end()) << endl;
    
    fill(vec.begin(), vec.end(), 0);

    for_each(vec.begin(), vec.end(), [](int i){cout << i << endl;});    
}