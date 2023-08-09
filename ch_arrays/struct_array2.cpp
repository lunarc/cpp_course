#include <iostream>

using namespace std;

struct coord3D {
    double x;
    double y;
    double z;
};

int main()
{
    coord3D** coords = new coord3D*[10];
    
    double counter = 0.0;
    
    for (auto i=0; i<10; i++)
    {
        coords[i] = new coord3D;
        coords[i]->x = counter++;
        coords[i]->y = counter++;
        coords[i]->z = counter++;
    }
    
    for (auto i=0; i<10; i++)
        cout << coords[i]->x << ", " << coords[i]->y << ", " << coords[i]->z << endl;
    
    for (auto i=0; i<10; i++)
        delete coords[i];

    delete [] coords;
}
