#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s1 = "hello";
    string s2 = ", world";
    string s3 = s1 + s2;

    s3.append(". Strings in C++ are great!");
    cout << "s3 = " << s3 << endl;
    
    s3.replace(33, 6, "nice! ");
    cout << "s3 = " << s3 << endl;
    
    s3.insert(33, "great and ");
    cout << "s3 = " << s3 << endl;
    
    string s4 = s3.substr(33, 6);
    cout << "s4 = " << s4 << endl;
    
}