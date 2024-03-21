# Object-oriented programming

In procedural programming, data and subroutines are treated separately. Subroutines operate on provided data structures and variables. In object-oriented programming data and subroutines are combined into objects. Objects in numerical computing can be different matrix types, particles, vectors or solvers. The major benefits are that the actual data structures used in the implementation of an object can be hidden from the user of the object, enabling the developer of an object to improve the implementation without affecting users of the objects (encapsulation). Another important feature of object-oriented programming is the ability to inherit and extend the functionality of objects (inheritance). This enables users of objects and developers to extend and modify the functionality of existing objects, relying on the functionality of the parent object.

The functionality and data structures of objects are defined in classes in most programming object-oriented languages. Classes can be seen as templates or blueprints for objects. When an object is to be created the class is used as the template to construct the new object. Created objects are also called instances of a class.

* Normal programs can be seen as several tasks/functions to perform. 
* An object-oriented program can be seen as several interacting objects
* Objects can receive messages, process data, and send messages to other objects
* Objects hide data from view. Access through methods
* Object-oriented can be traced back to Simula 67

Key features

* Dynamic dispatch (late binding)
  - The actual method called is determined at runtime
  - Enabled Polymorphism
* Polymorphism
  - Several objects share characteristics
  - Shape – Circle, Rectangle, Oval
* Encapsulation
  - Combine data and function in a single entity
  - Restricting access to actual data
* Inheritance
  - Reuse code of an existing object/classes
  - Inherit attributes from existing classes

## Classes in C++

C++ introduces the concept of a class. A class can be seen as a combination of data and functions/methods into a single entity, the class. As a language concept, it is very close to the basic struct data type in C++ in which data fields can be combined into a single user-defined data type. The class concept extends the struct data type with access methods and access attributes. The idea is that class attributes should only be accessed using methods, to hide the underlying implementation.

An example of a class could be a point with a position. We can add methods for moving the point, getting and setting the point coordinates and printing the point coordinates. The first step is shown in the following example:

```cpp
class Point {
    float m_x{};
    float m_y{};
};
```

In this example, we declare a class **Point** that has two member attributes **m_x** and **m_y**. The class declaration can be seen as a template of an object. To create a **Point** object we declare it just like any other variable in C++ by specifying the class **Point** as the type and giving a name of the object as shown in the code below:

```cpp
Point p;
```

However if we access the member variables, **m_x** and **m_y**

```cpp
std::cout << p.m_x << ", " << m_y << "\n";
```

will produce the following error

```
cannot access private member Point::m_x
  member declared at example.cpp:4:11
    std::cout << p.m_x << "\n"; 
```

[:fontawesome-solid-gears: Try example](https://godbolt.org/z/d978a8T8z){ .md-button  .target="_blank"}

which is completely correct. By default, all attributes of a class are private, which means that we cannot access the **Points** member functions. To access these member attributes we need to add access methods. To do this we need to declare public access methods in our class. In addition to doing this, we also need to specify attributes to tell the compiler which parts of the class are private and public. This is done using the **private:** and **public:** class attributes. The modified class then becomes:

```cpp
#include <iostream>

class Point {
private:
    float m_x{};
    float m_y{};
public:
    void setX(float x) 
    { 
        m_x = x; 
    };
    
    void setY(float y)
    { 
        m_y = y; 
    };

    float x()
    { 
        return m_x; 
    };
    float y() 
    { 
        return m_y; 
    };
};

int main()
{
    Point p;
    p.setX(1.0);
    p.setY(2.0);

    std::cout << p.x() << ", " << p.y() << "\n";
}
```

In this code, we have added 4 methods 2 for assigning the **m_x** and **m_y** attributes and 2 methods for returning the values of the attributes. In this, the user of the instance **p** doesn't need to know how the actual storage of the coordinates is implemented. They could be stored in a remote database, but the way of assigning and retrieving the values stays the same. 





A class can be seen as a struct that contain functions for accessing data

Variables and methods of a class can be 

* private – Not accessible by derived classes and from instance.
* protected – Accessible by derived classes but not from instance.
* public – Accessible by derived classes and from instance

A class is a blueprint for an instance or object

An instance can be created on the stack or on the heap using the new operator

A Class often represents a noun such as a person, particle, shape

## Declaring classes in C++

## Instantiating classes

## Implementing a graphics library

### Finding shared characteristics



## Object-oriented analysis

Object relationships

* has – A car has wheels (aggregation)
* has – A particle system has particles (composite)
* is – A Triangle is a Shape (specialisation inheritance)

### Aggregation

### Composite

### Identifying classes





