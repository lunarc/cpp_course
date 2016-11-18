#include <iostream>

using namespace std;

int main()
{
    char c;
    unsigned char uc;
    signed char sc;
    
    c = 'a';
    uc = 129;
    sc = 130;
    
    cout << "c = " << c << " int(c) = " << int(c);
    cout << " sizeof(c) = " << sizeof(c) << endl;
    cout << "uc = " << uc << " int(uc) = " << int(uc);
    cout << " sizeof(c) = " << sizeof(c) << endl;
    cout << "sc = " << sc << " int(sc) = " << int(sc);
    cout << " sizeof(c) = " << sizeof(c) << endl;
}
