#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s = "The quick brown fox jumps over the lazy dog.";
    
    auto p0 = s.find("o");
    auto p1 = s.find("o", p0+1);
    auto p2 = s.find("xx");
    
    cout << "The first 'o' is at position " << p0 << "\n";
    cout << "The next 'o' is at position " << p1 << "\n";

    if (p2 == string::npos)
        cout << "xx was not found.\n";
    else
        cout << "xx was found.\n";
}
