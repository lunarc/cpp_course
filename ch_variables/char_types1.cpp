#include <iostream>

using namespace std;

int main()
{
    char c;
    unsigned char uc;
    signed char sc;
    char16_t c16;
    char32_t c32;
    wchar_t w32;

    c = 'a';
    uc = 170;
    sc = 130;

    c16 = 'b';
    c32 = 'c';
    w32 = 'd';

    cout << "c = " << c << " int(c) = " << int(c);
    cout << " sizeof(c) = " << sizeof(c) << endl;
    cout << "uc = " << uc << " int(uc) = " << int(uc);
    cout << " sizeof(c) = " << sizeof(c) << endl;
    cout << "sc = " << sc << " int(sc) = " << int(sc);
    cout << " sizeof(c) = " << sizeof(c) << endl;
    wcout << "c16 = " << wchar_t(c16) << " int(c16) = " << int(c16);
    cout << " sizeof(c16) = " << sizeof(c16) << endl;
    wcout << "c32 = " << wchar_t(c32) << " int(c32) = " << int(c32);
    cout << " sizeof(c32) = " << sizeof(c16) << endl;
    wcout << "w32 = " << wchar_t(w32) << " int(w32) = " << int(w32);
    cout << " sizeof(w32) = " << sizeof(w32) << endl;
}
