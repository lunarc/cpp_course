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
    
    m.erase(m.find("mike"));

    cout << "--" << endl;
    
    for (it=m.begin(); it!=m.end(); it++)
        cout << it->first << ", " << it->second << endl;
    
    m.insert(pair<string,int>("carl", 43));

    cout << "--" << endl;
    
    for (it=m.begin(); it!=m.end(); it++)
        cout << it->first << ", " << it->second << endl;
    
    m.clear();
    
    cout << "--" << endl;
    
    for (it=m.begin(); it!=m.end(); it++)
        cout << it->first << ", " << it->second << endl;
    
    cout << "m.size() = " << m.size() << endl;

}