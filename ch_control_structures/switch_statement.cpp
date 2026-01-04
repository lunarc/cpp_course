#include <print>
#include <cstdlib>
#include <ctime>

int main()
{
    enum colorType { RED, GREEN, BLUE, YELLOW, ORANGE };
    srand((unsigned)time(0));
    
    
    for (int i=0; i<4; i++)
    {
        colorType color = colorType(rand()%5);
        switch (color)
        {
            case RED:
                std::println("Color is red.");
                break;
            case GREEN:
                std::println("Color is green.");
                break;
            default:
                std::println("Color is either BLUE, YELLOW or ORANGE.");
                break;
        }
    }
}