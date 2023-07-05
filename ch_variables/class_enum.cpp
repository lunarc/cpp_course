#include <iostream>

using namespace std;

int main()
{
    enum class Color
    {
        Grey,
        Cyan,
        Purple
    };

    Color color = Color::Cyan;

    if (color == Color::Cyan)
        cout << "Color is Cyan" << endl;
    else
        cout << "Color is not Cyan" << endl;
}
