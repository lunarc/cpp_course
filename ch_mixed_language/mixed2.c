#include <stdio.h>

#include "point.h"

int main() 
{
    PointHandle p1 = point_create(0.0, 0.0);
    PointHandle p2 = point_create(3.0, 4.0);

    double dist = point_distance(p1, p2);

    printf("Distance between points: %f\n", dist);

    point_destroy(p1);

    return 0;
}