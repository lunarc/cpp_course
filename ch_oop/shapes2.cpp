#include <iostream>
#include <vector>
#include <memory>

using namespace std;

#include "point.h"
#include "circle.h"
#include "rectangle.h"

int main()
{
    vector<Shape*> shapes;
    vector<Shape*>::iterator si;
    
    cout << "adding objects ---" << endl;
    
    shapes.push_back(new Point(0.0, 0.0));
    shapes.push_back(new Circle(1.0, 0.0, 2.0));
    shapes.push_back(new Rectangle(0.0, 1.0, 2.0, 1.0));
    
    for (si=shapes.begin(); si!=shapes.end(); si++)
        (*si)->print();
    
    for (si=shapes.begin(); si!=shapes.end(); si++)
        delete *si;
    
    shapes.clear();
}