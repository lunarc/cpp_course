#include <iostream>
#include <limits>

using namespace std;

int main()
{
    cout << "Max, char " << int(numeric_limits<char>::max()) << endl;
    cout << "Min, char " << int(numeric_limits<char>::min()) << endl;
    cout << "Is char signed " << numeric_limits<char>::is_signed << endl;
    cout << "Max, unsigned char " << int(numeric_limits<unsigned char>::max()) << endl;
    cout << "Min, unsigned char " << int(numeric_limits<unsigned char>::min()) << endl;
    cout << "Max, short " << numeric_limits<short>::max() << endl;
    cout << "Min, short " << numeric_limits<short>::min() << endl;
    cout << "Max, int " << numeric_limits<int>::max() << endl;
    cout << "Min, int " << numeric_limits<int>::min() << endl;
    cout << "Max, long " << numeric_limits<long>::max() << endl;
    cout << "Min, long " << numeric_limits<long>::min() << endl;
    cout << "Max, float " << numeric_limits<float>::max() << endl;
    cout << "Min, float " << numeric_limits<float>::min() << endl;
    cout << "Max, double " << numeric_limits<double>::max() << endl;
    cout << "Min, double " << numeric_limits<double>::min() << endl;
    cout << "Max, long double " << numeric_limits<long double>::max() << endl;
    cout << "Min, long double " << numeric_limits<long double>::min() << endl;
}
