#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    const char* cString;
    char cString2[128];
    
    string cppString = "Hello, world!";
    
    cString = cppString.c_str();
    
    cout << "cString = " << cString << endl;
    
    strncpy(cString2, cppString.c_str(), cppString.length()+1);
    
    cout << "cString2 = " << cString2 << endl;
}