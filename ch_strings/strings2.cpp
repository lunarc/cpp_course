#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s1 = "hello";
    string s2 = ", world";
    string s3 = s1 + s2;
    cout << "s3 = '" << s3 << "'" << endl;
    cout << "s3.length() = " << s3.length() << endl;
    cout << "s3[7] = " << s3[7] << endl;
    cout << "s3.at(7) = " << s3.at(7) << endl;
}