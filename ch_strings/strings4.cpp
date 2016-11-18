#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s = "The quick brown fox jumps over the lazy dog.";
    
    int p0 = s.find("o");
    int p1 = s.find("o", p0+1);
    
    cout << "The first 'o' is at position " << p0 << endl;
    cout << "The next 'o' is at position " << p1 << endl;
}