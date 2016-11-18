#include "composite.h"

#include <iostream>
#include <cmath>

using namespace std;

Composite::Composite(double x, double y)
:Shape(x, y)
{
    this->setName("Composite");
}

Composite::~Composite()
{
    this->clear();
}

void Composite::print()
{
    Shape::print();
    cout << "Number of shapes = " << m_shapes.size() << endl;
}

double Composite::area()
{
    double totalArea = 0.0;
    
    vector<Shape*>::iterator it;
    
    for (it=m_shapes.begin(); it!=m_shapes.end(); it++)
        totalArea += (*it)->area();
    
    return totalArea;
}

void Composite::add(Shape* shape)
{
    m_shapes.push_back(shape);
}

void Composite::remove(Shape* shape)
{
    vector<Shape*>::iterator it;
    
    it = find(m_shapes.begin(), m_shapes.end(), shape);
    
    if (it!=m_shapes.end())
    {
        Shape* shape = *it;
        m_shapes.erase(it);
        delete shape;
    }
}

void Composite::clear()
{
    vector<Shape*>::iterator it;
    
    for(it=m_shapes.begin(); it!=m_shapes.end(); it++)
        delete *it;
    
    m_shapes.clear();
}

int Composite::count()
{
    return m_shapes.size();
}

Shape* Composite::at(int idx)
{
    if ((idx>=0)&&(idx<m_shapes.size()))
        return m_shapes[idx];
    else
        return 0;
}
