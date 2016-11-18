#include <iostream>
#include <vector>
#include <memory>

using namespace std;

#include "point.h"
#include "circle.h"
#include "rectangle.h"
#include "composite.h"

int main()
{
    Composite* composite = new Composite(0.0, 0.0);
    
    cout << "adding objects ---" << endl;
    
    composite->add(new Point(0.0, 0.0));
    composite->add(new Circle(1.0, 0.0, 2.0));
    composite->add(new Rectangle(0.0, 1.0, 2.0, 1.0));
    
    for (int i=0; i<composite->count(); i++)
        composite->at(i)->print();
        
    composite->remove(composite->at(0));
        
    cout << composite->count() << endl;
                
    composite->clear();
                        
    cout << composite->count() << endl;
    
    delete composite;
}