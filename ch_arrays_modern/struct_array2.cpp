#include <iostream>
#include <memory>

using namespace std;

struct Coord3D
{
    double x;
    double y;
};

typedef std::unique_ptr<Coord3D> Coord3DPtr;

int main()
{
    auto coords = std::make_unique<std::unique_ptr<Coord3D>[]>(10);
    // auto coords2 = std::make_unique<Coord3DPtr[]>(10);

    double counter = 0.0;

    for (int i = 0; i < 10; i++)
    {
        coords[i] = std::make_unique<Coord3D>();
        coords[i]->x = counter++;
        coords[i]->y = counter++;
    }

    for (int i = 0; i < 10; i++)
        cout << coords[i]->x << ", " << coords[i]->y << endl;
}
