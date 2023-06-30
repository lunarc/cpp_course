#include <iostream>
#include <limits>

using namespace std;

int main()
{
    cout << "Max, char " << int(std::numeric_limits<char>::max()) << endl;
    cout << "Min, char " << int(std::numeric_limits<char>::min()) << endl;
    cout << "Is char signed " << std::numeric_limits<char>::is_signed << endl;
    cout << "Max, unsigned char " << int(std::numeric_limits<unsigned char>::max()) << endl;
    cout << "Min, unsigned char " << int(std::numeric_limits<unsigned char>::min()) << endl;
    cout << "Max, short " << std::numeric_limits<short>::max() << endl;
    cout << "Min, short " << std::numeric_limits<short>::min() << endl;
    cout << "Max, int " << std::numeric_limits<int>::max() << endl;
    cout << "Min, int " << std::numeric_limits<int>::min() << endl;
    cout << "Max, long " << std::numeric_limits<long>::max() << endl;
    cout << "Min, long " << std::numeric_limits<long>::min() << endl;
    cout << "Max, float " << std::numeric_limits<float>::max() << endl;
    cout << "Min, float " << std::numeric_limits<float>::min() << endl;
    cout << "Max, double " << std::numeric_limits<double>::max() << endl;
    cout << "Min, double " << std::numeric_limits<double>::min() << endl;
    cout << "Max, long double " << std::numeric_limits<long double>::max() << endl;
    cout << "Min, long double " << std::numeric_limits<long double>::min() << endl;
}
