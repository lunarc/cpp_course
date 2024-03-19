#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v;
    
    for (auto i=0; i<5; i++)
        v.push_back(i);

    for (auto value : v)
        cout << value << endl;
        
    for (const auto& value : v)
        cout << value << endl;
        
    int array[] = {42,43,44,45,46};
    
    for (auto& value : array)
        cout << value << endl;
}
    
    