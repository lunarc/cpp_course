#include <print>

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
        std::println("Color is Cyan");
    else
        std::println("Color is not Cyan");
}
