#include <iostream>

using namespace std;

struct coord3D {
    double x;
    double y;
};

int main()
{
    coord3D* coords = new coord3D[10];
    
    double counter = 0.0;
    
    for (int i=0; i<10; i++)
    {
        coords[i].x = counter++;
        coords[i].y = counter++;
    }
    
    for (int i=0; i<10; i++)
        cout << coords[i].x << ", " << coords[i].y << endl;

    delete [] coords;
}