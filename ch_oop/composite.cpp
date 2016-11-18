#include "composite.h"

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

Composite::Composite(double x, double y)
:Shape(x, y)
{
    this->setName("Composite");
}

Composite::~Composite()
{
    cout << "Composite destructor called." << endl;
    this->clear();
}

void Composite::print()
{
    Shape::print();
    cout << "Number of shapes = " << m_shapes.size() << endl;

    for (auto v : m_shapes)
        v->print();
}

double Composite::area()
{
    double totalArea = 0.0;
    
    for (auto shape : m_shapes)
        totalArea += shape->area();
    
    return totalArea;
}

void Composite::add(Shape* shape)
{
    m_shapes.push_back(shared_ptr<Shape>(shape));
}

void Composite::remove(Shape* shape)
{    
    for (auto it=m_shapes.begin(); it!=m_shapes.end(); it++)
    {
        if ((*it).get() == shape)
        {
            m_shapes.erase(it);
            return;
        }
    }
}

void Composite::clear()
{
    m_shapes.clear();
}

int Composite::count()
{
    return m_shapes.size();
}

Shape* Composite::at(int idx)
{
    if ((idx>=0)&&(idx<m_shapes.size()))
        return m_shapes[idx].get();
    else
        return 0;
}
