#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    map<string,int> m;
    
    m["bob"] = 42;
    m["alice"] = 40;
    m["mike"] = 30;
    m["richard"] = 25;
    
    for (auto it=m.begin(); it!=m.end(); it++)
        cout << it->first << ", " << it->second << endl;
    
    auto it = m.find("bob");
    cout << "found: " << it->first << ", " << it->second << endl;
    
    it = m.find("carl");
    
    if (it!=m.end())
        cout << "found: " << it->first << ", " << it->second << endl;
    else
        cout << "Could not find Carl." << endl;
    
}