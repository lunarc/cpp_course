#include <iostream>
#include <memory>

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

    std::unique_ptr<Rectangle> rect2(new Rectangle(1.0, 1.0, 3.0, 3.0));
    rect2->print();

    std::unique_ptr<Rectangle> rect3(std::move(rect2));
    rect3->print();

    //  rect2->print();  // Not allowed

    std::shared_ptr<Rectangle> rect4(new Rectangle(2.0, 2.0, 4.0, 4.0));
    std::shared_ptr<Rectangle> rect5(nullptr);

    rect5 = rect4;

    std::shared_ptr<Rectangle> rect6(rect5);

    rect5->print();
    rect4->print();

    cout << rect4.use_count() << endl;

}
