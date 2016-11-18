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
    shared_ptr<Composite> composite(new Composite(0.0, 0.0));
    
    cout << "adding objects ---" << endl;
    
    composite->add(new Point(0.0, 0.0));
    composite->add(new Circle(1.0, 0.0, 2.0));
    composite->add(new Rectangle(0.0, 1.0, 2.0, 1.0));
    
    composite->print();

    composite->remove(composite->at(0));

    composite->print();
}
