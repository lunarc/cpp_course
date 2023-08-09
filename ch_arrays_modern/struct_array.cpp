#include <iostream>
#include <memory>

using namespace std;

struct coord3D
{
    double x;
    double y;
};

int main()
{
    auto coords = std::make_unique<coord3D[]>(10);

    double counter{0.0};

    for (auto i = 0; i < 10; i++)
    {
        coords[i].x = counter++;
        coords[i].y = counter++;
    }

    for (int i = 0; i < 10; i++)
        cout << coords[i].x << ", " << coords[i].y << endl;
}
