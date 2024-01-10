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

    Circle c1(0.5, 1.0, 2.0);
    c1.print();

    Circle c2(0.5, 3.0, 1.0);
    c2.print();

    c1 = c2;

    c1.print();

    if (c1 == c2)
		cout << "c1 and c2 are equal" << endl;
	else
		cout << "c1 and c2 are not equal" << endl;

    auto rect = new Rectangle(0.0, 0.0, 1.0, 2.0);
    rect->print();
    delete rect;

    auto rect2 = make_shared<Rectangle>(1.0, 1.0, 3.0, 3.0);
    rect2->print();

    auto rect3(std::move(rect2));
    rect3->print();

    //  rect2->print();  // Not allowed

    std::shared_ptr<Rectangle> rect4 = make_shared<Rectangle>(2.0, 2.0, 4.0, 4.0);
    std::shared_ptr<Rectangle> rect5;

    rect5 = rect4;

    auto rect6(rect5);

    rect5->print();
    rect4->print();

    cout << rect4.use_count() << endl;

}
