#include <iostream>

using namespace std;

#include "point.h"
#include "circle.h"
#include "rectangle.h"

int main()
{
    Point p0(1.0, 1.0);
    Point p1(1.0, 1.0);
    
    p0.print();
    p1.print();
    
    Circle c0(0.5, 1.0, 2.0);
    c0.print();
    
    Rectangle r0(0.0, 0.0, 2.0, 1.0);
    r0.print();
    
    Rectangle* rect = new Rectangle(0.0, 0.0, 1.0, 2.0);
    rect->print();
    delete rect;
    
}