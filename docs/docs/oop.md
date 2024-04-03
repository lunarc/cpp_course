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
   * The actual method called is determined at runtime
   * Enabled Polymorphism
 * Polymorphism
   * Several objects share characteristics
   * Shape – Circle, Rectangle, Oval
 * Encapsulation
   * Combine data and function in a single entity
   * Restricting access to actual data
 * Inheritance
   * Reuse code of an existing object/classes
   * Inherit attributes from existing classes

## Classes in C++

C++ introduces the concept of a class. A class can be seen as a combination of data and functions/methods into a single entity, the class. As a language concept, it is very close to the basic struct data type in C++ in which data fields can be combined into a single user-defined data type. The class concept extends the struct data type with access methods and access attributes. The idea is that class attributes should only be accessed using methods, to hide the underlying implementation.

An example of a class could be a vector with x and y components. We can add methods for translating the vector, getting and setting the vector components and printing the component values. The first step is to define the class and the attribute variables for the coordinates, **m_x** and **m_y**, as shown in the following code:

```cpp
class Vector {
    float m_x{};
    float m_y{};
};
```

The class declaration can be seen as a template of an object. To create a **Point** object we declare it just like any other variable in C++ by specifying the class **Point** as the type and giving a name of the object as shown in the code below:

```cpp
Vector v;
```

However if we access the member variables, **m_x** and **m_y**

```cpp
std::cout << v.m_x << ", " << v.m_y << "\n";
```

will produce the following error

```
cannot access private member Vector::m_x
  member declared at example.cpp:4:11
    std::cout << v.m_x << "\n"; 
```

[:fontawesome-solid-gears: Try example](https://godbolt.org/z/WqYYEKr5r){ .md-button  .target="_blank"}

which is expected behavior. By default, all attributes of a class are private, which means that we cannot access the **Vector** member functions. To access these member attributes we need to add access methods. To do this we need to declare public access methods in our class. In addition to doing this, we also need to specify attributes to tell the compiler which parts of the class are private and public. This is done using the **private:** and **public:** class attributes. The modified class then becomes:

```cpp
#include <iostream>

class Vector {
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

    void set(float x, float y)
    {
        m_x = x;
        m_y = y;
    }

    float x()
    { 
        return m_x; 
    };

    float y() 
    { 
        return m_y; 
    };

    void print()
    {
        std::cout << "(" << m_x << ", " << m_y << ")\n";
    }

};

int main()
{
    Vector v;
    v.set(1.0, -2.0);
    
    std::cout << p.x() << ", " << p.y() << "\n";

    p.print();
}
```

In this code, we have added 6 methods 3 for assigning the **m_x** and **m_y** attributes and 2 methods for returning the values of the attributes. By using access methods like in this way, the user of the object **v** doesn't need to know how the actual storage of the components is implemented. They could be stored in a remote database, but the way of assigning and retrieving the values stays the same. 

[:fontawesome-solid-gears: Try example](https://godbolt.org/z/PW5j98ave){ .md-button  .target="_blank"}

## Class initialisation

When declaring class variables it is important that the default state of the variables are initialised. This can be done in several ways. The easiest way is to assign default values in the declaration of class variable. In the **Vector** class this was done using the {}-brackets:

```cpp
float m_x{};
float m_y{};
```

Using empty brackets will initialise the variable to its default value most of the time 0 or 0.0. It is also possible to initial values by using a class constructor. A class constructor is a special function that is called when a new object is created. This method can be used to initialise variables and do more complex initialisation operations that can't be handled by default initialisation procedures. In the following code we have added a constructor that initialises the **m_x** and **m_y** class variables. Note that initialisation of class variables is done before the body of the function. It is possible to initialise the variables in the function body, but that is not as efficient.

```cpp
#include <iostream>

class Vector {
private:
    float m_x{};
    float m_y{};
public:
    Vector()
        :m_x{-1.0}, m_y{-2.0}
    {
        std::cout << "Vector() constructor called.\n";
    }    
    ...
```

If we create a **Vector** instance with the following code:

```cpp
Vector v;

v.print();
```

will produce the following output:

```
Vector() constructor called.
(-1, -2)
```

We can clearly see that the constructor is called when the **Vector** object is created. We can also see that the member variables have changed their default values to -1 and -2.

## Constructor with arguments

For our **Vector** class it would also be nice to be able to create an object in a single statement where we give it the vector components in the declaration. This can be done by modifying our existing class constructor:

```cpp
class Vector {
private:
    float m_x{};
    float m_y{};
public:
    Vector(float x=0.0, float y=0.0)
    :m_x{x}, m_y{y}
    {}
    ...
```

By using default arguments to the constructor it is still possible to declare a **Vector** object without any arguments. A vector can now be created using the following code:

```cpp
Vector v{1.0, -2.0};
```

If no constructor is declared, C++ will automatically generate default constructors for your class. For simple classes this is often enough, for more complex classes these constructors need to be provided by the classes. The following example shows when the different constructors are used:

```cpp
Vector v0;            // Default constructor
Vector v1{1.0, -2.0}; // Default or constructor with arguments.
Vector v2 = v1;       // Copy constructor
v0 = v2;              // Assignment operator
```

## The copy constructor

A special constructor is called when initialising a new object by assigning an existing object. It looks like the code below:

```cpp
Vector v2 = v1;
```

In the constructor we need to copy the values of the **v1** object into the new object **v2**. Adding a copy constructor to the **Vector** class is shown below:

```cpp
Vector(const Vector& other)
: m_x{other.m_x}, m_y{other.m_y}
{}
```

In the constructor we initialise the local class variables with the **other** objects corresponding variables. Please note that the incoming **other** object is declared as const and passed by reference. This avoids copying of the object and accidental modification.

## The assignment operator

A similar operation to the copy constructor is the assignment operator. This operator is called when one object is assigned from a another object. As shown in the followng code:

```cpp
v0 = v2; // Assignment operator
```

To implement an assignment operator we add the following code to our class:

```cpp
Vector& operator=(const Vector& other)
{
    m_x = other.m_x;
    m_y = other.m_y;
    return *this;
}
```

The difference from the copy constructor is that the assignment is done in the function body and we need to return a pointer to our own object (*this).

## Implementing vector operations

To perform vector operations such as addition, subtraction, and scalar multiplication, we can add member functions to our **Vector** class. In C++, all operators in the language can be implemented as special methods added to our class implementation. The + operator is implemented using the special **operator+(...)** method. An example implementation of this operator is shown in the class below:

```cpp
Vector operator+(const Vector& other) const {
    return Vector(m_x + other.m_x, m_y + other.m_y);
}
```

We can now perform operations such as:

```cpp
Vector v1{1.0, 1.0};
Vector v2{2.0, 2.0};
Vector v3 = v1 + v2; // Copy constructor + operator+(...) 
```

We can now add other operator methods in the same way. Functions for calculating scalar and cross products can be added as additional class methods.

```cpp
float Vector::dot(const Vector& other) const {
	return m_x * other.m_x + m_y * other.m_y;
}

float Vector::cross(const Vector& other) const {
	return m_x * other.m_y - m_y * other.m_x;
}
```

Cross products and scalar product can now be calculated as shown in the following code:

```cpp
Vector v5{ 1.0, 0.0 };
Vector v6{ 0.0, 1.0 };

cout << "v5.dot(v6) = " << v5.dot(v6) << endl;
cout << "v5.cross(v6) = " << v5.cross(v6) << endl;
```

Which gives the following output:

```
v5.dot(v6) = 0
v5.cross(v6) = 1
```

We can also add a convenient **length()** method:

```cpp
double Vector::length() const
{
	return std::sqrt(this->dot(*this));
}
```

Calculating the length of a vector can now be done by calling the **.length()**-method.

```cpp
cout << "v5.length() = " << v5.length() << endl;
```

Which gives us the length of 1:

```
v5.length() = 1
```

!!! note

    The reason we add the **const** keyword in functions and argument lists is to indicate behavior to the compiler. The compiler can check for variable modifications and also generate more efficient code if it knows that a function will not modify the member variables of a class. 

## Inheritance

One of the key concepts of object-oriented programming is inheritance. Using this concept we can define new classes that inherit behavior and attributes from existing classes. This can be beneficial for example if we would design a graphics library. In our library we want to be able to draw shapes on the screen. Many of these shapes share attributes such as position, fill color and line color. There could also be methods for moving and querying the area of a shape. 

### Defining a base class Shape

To define our classes we start by definining a base class, in this case it could be **Shape**. For our shape we need to be able to place the shape on the 2D screen, so we need attributes for position, fill color, line color and a display name. The code below shows an example of how a base class for our class library could look like.

```cpp
class Shape {
private:
    double m_x{};
    double m_y{};
    double m_fillColor[4]{ 1.0, 0.0, 0.0, 1.0};
    double m_lineColor[4]{ 0.0, 0.0, 0.0, 1.0};
    std::string m_name{};
public:
    Shape();
    Shape(double x, double y);
    
    ...    
    
    void setPosition(double x, double y);
    double x() const;
    double y() const;

    void setFillColor(double r, double g, double b, double a);
    void setLineColor(double r, double g, double b, double a);

    void getFillColor(double& r, double& g, double& b, double& a) const;
    void getLineColor(double& r, double& g, double& b, double& a) const;

    void setName(const std::string& name);
    std::string name() const;
};
```

We also need some common methods for our new **Shape** class such as **.draw()**, **.print()** and **.area()**. These methods should be implemented by other inherited classes and only skeleton implementations are provided by **Shape**. Methods that are supposed to be overridden by inherited classes should be marked with **virtual**. This also makes it possible for the correct methods to be called when working with a collection of different types of shapes. The following code is added to the class:

```cpp
public:
    ...
    virtual void print() const;
    virtual double area() const;
    virtual void draw() const;
    ...
```

### Implementing a Circle shape.

To implement a **Circle** shape we create a new class definition inheriting from the **Shape** class.

```cpp
class Circle : public Shape {
private:
    double m_radius{1.0};
public:
    Circle(double x = 1.0, double y = 1.0, double radius = 1.0);

    virtual void print() const override;
    virtual double area() const override;
    virtual void draw() const override;
    
    double radius() const;
    void setRadius(double radius);
};
```
Inheritance in a class is defined by adding **: public Shape** after the class name in the class definition. This tells the compiler that **Circle** inherits all of the public interface of the **Shape** class. This means that the **Circle** class can't access any of the private methods or attributes from the **Shape**, which is what we want. 

As we have an additional attribute, **radius**, we need to create suitable constructors. We also need to pass our constructor arguments to the **Shape** constructor and initialize the circle **m_radius** attribute. This is done just before the constructor code block. 

```cpp
Circle::Circle(double x, double y, double radius)
	: Shape(x, y)
    , m_radius{radius}
{
	this->setName("Circle");
}

To be able to draw a circle we need to override some of the methods of the **Shape** class such as **print()**, **area()** and **draw()**. 

The implementation of these classes are shown below:

```cpp
void Circle::print() const
{
	Shape::print();
	cout << "radius = " << m_radius << endl;
}

double Circle::area() const
{
	double pi = 4 * std::atan(1);
	return pow(m_radius, 2) * pi;
}

void Circle::draw() const
{
	Shape::draw();
	// Draw a circle
	cout << "Drawing a circle at: (" << x() << ", " << y() << ")" << endl;
	cout << "Circle radius: " << m_radius << endl;
}
```

Notice that as we are overriding the **print()**-method of the **Shape** class. If we need any functionality of the base class we need to explicitely call this method from our overridden method, as shown in the **print()** and **draw()** method. For the **area()** method this is not required as we don't need any functionality from the **Shape** **area()** method.



















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





