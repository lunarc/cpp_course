#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    map<string,int> m;
    map<string,int>::iterator it;
    
    m["bob"] = 42;
    m["alice"] = 40;
    m["mike"] = 30;
    m["richard"] = 25;
    
    for (it=m.begin(); it!=m.end(); it++)
        cout << it->first << ", " << it->second << endl;
    
    it = m.find("bob");
    cout << "found: " << it->first << ", " << it->second << endl;
    
    it = m.find("carl");
    
    if (it!=m.end())
        cout << "found: " << it->first << ", " << it->second << endl;
    else
        cout << "Could not find Carl." << endl;
    
}