Object-oriented programming
===========================

In procedural programming, data and subroutines are treated separately.
Subroutines operate on provided data structures and variables. In
object-oriented programming data and subroutines are combined into
objects. Objects in numerical computing can be different matrix types,
particles, vectors or solvers. The major benefits are that the actual
data structures used in the implementation of an object can be hidden
from the user of the object, enabling the developer of an object to
improve the implementation without affecting users of the objects
(encapsulation). Another important feature of object-oriented
programming is the ability to inherit and extend the functionality of
objects (inheritance). This enables users of objects and developers to
extend and modify the functionality of existing objects, relying on the
functionality of the parent object.

The functionality and data structures of objects are defined in classes
in most programming object-oriented languages. Classes can be seen as
templates or blueprints for objects. When an object is to be created the
class is used as the template to construct the new object. Created
objects are also called instances of a class.

- Normal programs can be seen as several tasks/functions to perform.
- An object-oriented program can be seen as several interacting objects
- Objects can receive messages, process data, and send messages to other
  objects
- Objects hide data from view. Access through methods
- Object-oriented can be traced back to Simula 67

Key features

- Dynamic dispatch (late binding)

  - The actual method called is determined at runtime
  - Enabled Polymorphism

- Polymorphism

  - Several objects share characteristics
  - Shape – Circle, Rectangle, Oval

- Encapsulation

  - Combine data and function in a single entity
  - Restricting access to actual data

- Inheritance

  - Reuse code of an existing object/classes
  - Inherit attributes from existing classes

Classes in C++
--------------

C++ introduces the concept of a class. A class can be seen as a
combination of data and functions/methods into a single entity, the
class. As a language concept, it is very close to the basic struct data
type in C++ in which data fields can be combined into a single
user-defined data type. The class concept extends the struct data type
with access methods and access attributes. The idea is that class
attributes should only be accessed using methods, to hide the underlying
implementation.

An example of a class could be a vector with x and y components. We can
add methods for translating the vector, getting and setting the vector
components and printing the component values. The first step is to
define the class and the attribute variables for the coordinates,
**m_x** and **m_y**, as shown in the following code:

.. code:: cpp

   class Vector {
       float m_x{};
       float m_y{};
   };

The class declaration can be seen as a template of an object. To create
a **Point** object we declare it just like any other variable in C++ by
specifying the class **Point** as the type and giving a name of the
object as shown in the code below:

.. code:: cpp

   Vector v;

However if we access the member variables, **m_x** and **m_y**

.. code:: cpp

   std::cout << v.m_x << ", " << v.m_y << "\n";

will produce the following error

::

   cannot access private member Vector::m_x
     member declared at example.cpp:4:11
       std::cout << v.m_x << "\n"; 

`:fontawesome-solid-gears: Try
example <https://godbolt.org/z/WqYYEKr5r>`__\ { .md-button
.target=“\_blank”}

which is expected behavior. By default, all attributes of a class are
private, which means that we cannot access the **Vector** member
functions. To access these member attributes we need to add access
methods. To do this we need to declare public access methods in our
class. In addition to doing this, we also need to specify attributes to
tell the compiler which parts of the class are private and public. This
is done using the **private:** and **public:** class attributes. The
modified class then becomes:

.. code:: cpp

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

       float x() const
       { 
           return m_x; 
       };

       float y() const
       { 
           return m_y; 
       };

       void print() const
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

In this code, we have added 6 methods 3 for assigning the **m_x** and
**m_y** attributes and 2 methods for returning the values of the
attributes. By using access methods like in this way, the user of the
object **v** doesn’t need to know how the actual storage of the
components is implemented. They could be stored in a remote database,
but the way of assigning and retrieving the values stays the same.

`:fontawesome-solid-gears: Try
example <https://godbolt.org/z/PW5j98ave>`__\ { .md-button
.target=“\_blank”}

Class initialisation
--------------------

When declaring class variables it is important that the default state of
the variables are initialised. This can be done in several ways. The
easiest way is to assign default values in the declaration of class
variable. In the **Vector** class this was done using the {}-brackets:

.. code:: cpp

   float m_x{};
   float m_y{};

Using empty brackets will initialise the variable to its default value
most of the time 0 or 0.0. It is also possible to initial values by
using a class constructor. A class constructor is a special function
that is called when a new object is created. This method can be used to
initialise variables and do more complex initialisation operations that
can’t be handled by default initialisation procedures. In the following
code we have added a constructor that initialises the **m_x** and
**m_y** class variables. Note that initialisation of class variables is
done before the body of the function. It is possible to initialise the
variables in the function body, but that is not as efficient.

.. code:: cpp

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

If we create a **Vector** instance with the following code:

.. code:: cpp

   Vector v;

   v.print();

will produce the following output:

::

   Vector() constructor called.
   (-1, -2)

We can clearly see that the constructor is called when the **Vector**
object is created. We can also see that the member variables have
changed their default values to -1 and -2.

Constructor with arguments
--------------------------

For our **Vector** class it would also be nice to be able to create an
object in a single statement where we give it the vector components in
the declaration. This can be done by modifying our existing class
constructor:

.. code:: cpp

   class Vector {
   private:
       float m_x{};
       float m_y{};
   public:
       Vector(float x=0.0, float y=0.0)
       :m_x{x}, m_y{y}
       {}
       ...

By using default arguments to the constructor it is still possible to
declare a **Vector** object without any arguments. A vector can now be
created using the following code:

.. code:: cpp

   Vector v{1.0, -2.0};

If no constructor is declared, C++ will automatically generate default
constructors for your class. For simple classes this is often enough,
for more complex classes these constructors need to be provided by the
classes. The following example shows when the different constructors are
used:

.. code:: cpp

   Vector v0;            // Default constructor
   Vector v1{1.0, -2.0}; // Default or constructor with arguments.
   Vector v2 = v1;       // Copy constructor
   v0 = v2;              // Assignment operator

The copy constructor
--------------------

A special constructor is called when initialising a new object by
assigning an existing object. It looks like the code below:

.. code:: cpp

   Vector v2 = v1;

In the constructor we need to copy the values of the **v1** object into
the new object **v2**. Adding a copy constructor to the **Vector** class
is shown below:

.. code:: cpp

   Vector(const Vector& other)
   : m_x{other.m_x}, m_y{other.m_y}
   {}

In the constructor we initialise the local class variables with the
**other** objects corresponding variables. Please note that the incoming
**other** object is declared as const and passed by reference. This
avoids copying of the object and accidental modification.

The assignment operator
-----------------------

A similar operation to the copy constructor is the assignment operator.
This operator is called when one object is assigned from a another
object. As shown in the followng code:

.. code:: cpp

   v0 = v2; // Assignment operator

To implement an assignment operator we add the following code to our
class:

.. code:: cpp

   Vector& operator=(const Vector& other)
   {
       m_x = other.m_x;
       m_y = other.m_y;
       return *this;
   }

The difference from the copy constructor is that the assignment is done
in the function body and we need to return a pointer to our own object
(\*this).

Implementing vector operations
------------------------------

To perform vector operations such as addition, subtraction, and scalar
multiplication, we can add member functions to our **Vector** class. In
C++, all operators in the language can be implemented as special methods
added to our class implementation. The + operator is implemented using
the special **operator+(…)** method. An example implementation of this
operator is shown in the class below:

.. code:: cpp

   Vector operator+(const Vector& other) const {
       return Vector(m_x + other.m_x, m_y + other.m_y);
   }

We can now perform operations such as:

.. code:: cpp

   Vector v1{1.0, 1.0};
   Vector v2{2.0, 2.0};
   Vector v3 = v1 + v2; // Copy constructor + operator+(...) 

We can now add other operator methods in the same way. Functions for
calculating scalar and cross products can be added as additional class
methods.

.. code:: cpp

   float Vector::dot(const Vector& other) const {
       return m_x * other.m_x + m_y * other.m_y;
   }

   float Vector::cross(const Vector& other) const {
       return m_x * other.m_y - m_y * other.m_x;
   }

Cross products and scalar product can now be calculated as shown in the
following code:

.. code:: cpp

   Vector v5{ 1.0, 0.0 };
   Vector v6{ 0.0, 1.0 };

   cout << "v5.dot(v6) = " << v5.dot(v6) << endl;
   cout << "v5.cross(v6) = " << v5.cross(v6) << endl;

Which gives the following output:

::

   v5.dot(v6) = 0
   v5.cross(v6) = 1

We can also add a convenient **length()** method:

.. code:: cpp

   double Vector::length() const
   {
       return std::sqrt(this->dot(*this));
   }

Calculating the length of a vector can now be done by calling the
**.length()**-method.

.. code:: cpp

   cout << "v5.length() = " << v5.length() << endl;

Which gives us the length of 1:

::

   v5.length() = 1

!!! note

::

   The reason we add the **const** keyword in functions and argument lists is to indicate behavior to the compiler. The compiler can check for variable modifications and also generate more efficient code if it knows that a function will not modify the member variables of a class. 

Inheritance
-----------

One of the key concepts of object-oriented programming is inheritance.
Using this concept, we can define new classes that inherit behavior and
attributes from existing classes. This can be beneficial, for example,
if we were designing a graphics library. In our library, we want to be
able to draw shapes on the screen. Many of these shapes share attributes
such as position, fill color, and line color. There could also be
methods for moving and querying the area of a shape.

Defining a base class Shape
~~~~~~~~~~~~~~~~~~~~~~~~~~~

To define our classes, we start by defining a base class, in this case,
it could be **Shape**. For our shape, we need to be able to place the
shape on the 2D screen, so attributes are needed for position, fill
color, line color, and a display name. The code below shows an example
of how a base class for our class library could look:

.. code:: cpp

   class Shape {
   private:
       double m_x{};
       double m_y{};
       double m_fillColor[4]{ 1.0, 0.0, 0.0, 1.0 };
       double m_lineColor[4]{ 0.0, 0.0, 0.0, 1.0 };
       std::string m_name{};
   public:
       Shape();
       Shape(double x, double y);
       
       void setPosition(double x, double y);
       double x() const;
       double y() const;

       void setFillColor(double r, double g, double b, double a);
       void setLineColor(double r, double g, double b, double a);

       void getFillColor(double& r, double& g, double& b, double& a) const;
       void getLineColor(double& r, double& g, double& b, double& a) const;

       void setName(const std::string& name);
       std::string name() const;

       virtual void print() const;
       virtual double area() const;
       virtual void draw() const;
   };

We also need some common methods for our new **Shape** class such as
**.draw()**, **.print()** and **.area()**. These methods should be
implemented by other inherited classes and only skeleton implementations
are provided by **Shape**. Methods that are supposed to be overridden by
inherited classes should be marked with **virtual**. This also makes it
possible for the correct methods to be called when working with a
collection of different types of shapes. The following code is added to
the class:

.. code:: cpp

   public:
       ...
       virtual void print() const;
       virtual double area() const;
       virtual void draw() const;
       ...

.. code:: cpp

   public:
       ...
       virtual void print() const;
       virtual double area() const;
       virtual void draw() const;
       ...

Implementing a Circle shape.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To implement a **Circle** shape we create a new class definition
inheriting from the **Shape** class.

.. code:: cpp

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

Inheritance in a class is defined by adding **: public Shape** after the
class name in the class definition. This tells the compiler that
**Circle** inherits all of the public interface of the **Shape** class.
This means that the **Circle** class can’t access any of the private
methods or attributes from the **Shape**, which is what we want.

As we have an additional attribute, **radius**, we need to create
suitable constructors. We also need to pass our constructor arguments to
the **Shape** constructor and initialize the circle **m_radius**
attribute. This is done just before the constructor code block.

.. code:: cpp

   Circle::Circle(double x, double y, double radius)
       : Shape(x, y)
       , m_radius{radius}
   {
       this->setName("Circle");
   }

To be able to draw a circle we need to override some of the methods of
the **Shape** class such as **print()**, **area()** and **draw()**.

The implementation of these classes are shown below:

.. code:: cpp

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

Notice that as we are overriding the **print()**-method of the **Shape**
class. If we need any functionality of the base class we need to
explicitely call this method from our overridden method, as shown in the
**print()** and **draw()** method. For the **area()** method this is not
required as we don’t need any functionality from the **Shape**
**area()** method.

Instantiating classes
---------------------

To create an instance of a class we use the same syntax as for creating
a variable. The following code creates a **Circle** object and calls the
**print()** method.

.. code:: cpp

   Circle c{1.0, 1.0, 2.0};
   c.print();

The output of the code will be:

.. code:: cpp

   Shape: Circle
   Position: (1, 1)
   radius = 2

Instances created in this way are allocated on the stack. The stack is a
memory area that is automatically managed by the compiler. The stack is
used for local variables and function calls. The stack is fast and
efficient but has a limited size.

If more memory is required than the stack can provide, we need to
allocate memory on the heap. The heap is a memory area that is managed
by the operating system. Usually, the heap is slower than the stack but
can hold much more data.

If we want to allocate the object on the heap we can use the **new**
keyword. The following code creates a **Circle** object on the heap and
calls the **print()** method.

.. code:: cpp

   Circle* c = new Circle{1.0, 1.0, 2.0};
   c->print();

When we have allocated an object on the heap it has to be deallocated
when it is no longer needed. This is done using the **delete** keyword.
The following code shows how to deallocate the **Circle** object.

.. code:: cpp

   delete c;

The use of **new** and **delete** is discouraged in modern C++
programming. The reason for that is that it is easy to forget to
deallocate memory, which can lead to memory leaks. Modern C++
programming uses smart pointers to manage memory allocation and
deallocation. Smart pointers are a type of object that automatically
deallocates memory when it is no longer needed. The following code shows
how to create a **Circle** object using a smart pointer.

.. code:: cpp

   std::unique_ptr<Circle> c = std::make_unique<Circle>(1.0, 1.0, 2.0);
   c->print();

When the **c** object goes out of scope the smart pointer will
automatically delete the object.

The **std::unique_ptr** is a smart pointer that can only have one owner.
This means that the object can’t be copied or moved to another smart
pointer. If we need to transfer ownership of the object we can use the
**std::move** function. The following code shows how to transfer
ownership of the **c** object to a new smart pointer.

.. code:: cpp

   std::unique_ptr<Circle> c2 = std::move(c);

After this code **c** will be empty and **c2** will own the **Circle**
object.

If an object needs to be shared between multiple owners we can use the
**std::shared_ptr** smart pointer. The **std::shared_ptr** keeps track
of how many owners the object has and deallocates the object when the
last owner is destroyed. The following code shows how to create a
**Circle** object using a **std::shared_ptr**.

.. code:: cpp

   std::shared_ptr<Circle> c = std::make_shared<Circle>(1.0, 1.0, 2.0);
   c->print();

Using **std::shared_ptr** a pointer can easily be transferred to another
owner. The following code shows how to transfer ownership of the **c**
object to a new smart pointer.

.. code:: cpp

   std::shared_ptr<Circle> c2 = c;

After this code **c** and **c2** will both own the **Circle** object.
When the last owner is destroyed the object will be deallocated.

To illustrate how we can creata simple class that prints out when it is
created and destroyed.

.. code:: cpp

   class Test {
   public:
       Test() { std::printf("Test() constructor called.\n"); }
       ~Test() { std::printf("~Test() destructor called.\n"); }
   };

To test object lifetimes we can use curly brackets to limit the scope of
the object.

.. code:: cpp

   {
       Test t;
   }

The output of the code will be:

::

   Test() constructor called.
   ~Test() destructor called.

Which is the expected output. The object is created when the scope is
entered and destroyed when the scope is exited.

Let’s try the same thing using a smart pointer.

.. code:: cpp

   {
       std::unique_ptr<Test> t = std::make_unique<Test>();
   }

The output of the code will be:

.. code:: cpp

   Test() constructor called.
   ~Test() destructor called.

Which is the expected output. The object is created when the scope is
entered and destroyed when the scope is exited.

In the following example we illustrate how to use a shared pointer. In
this example we create a shared pointer and transfer ownership to a new
shared pointer inside another scope.

.. code:: cpp

   {
       std::printf("Outer scope\n");
       std::shared_ptr<Test> t = std::make_shared<Test>();
       std::printf("t.use_count() = %d\n", t.use_count());
       {
           std::printf("Inner scope\n");
           std::shared_ptr<Test> t2 = t;
           std::printf("t.use_count() = %d\n", t.use_count());
       }
       std::printf("Outer scope\n");
       std::printf("t.use_count() = %d\n", t.use_count());
   }

The output of the code will be:

.. code:: cpp

   Outer scope
   Test() constructor called.
   t.use_count() = 1
   Inner scope
   t.use_count() = 2
   Outer scope
   t.use_count() = 1
   ~Test() destructor called.

`:fontawesome-solid-gears: Try
example <https://godbolt.org/z/rj4Y3hhv7>`__\ { .md-button
.target=“\_blank”}

Polymorphism
------------

Polymorphism is the ability to operate on objects of different classes
in the same way. This is achieved by using pointers to the base class.
When a pointer to a base class is used to point to an object of a
derived class, the derived class object can be treated as if it was a
base class object. This is useful when working with collections of
objects of different classes. The following code shows how to create a
collection of **Shape** objects and call the **print()** method on each
object.

.. code:: cpp

   vector<std::shared_ptr<Shape>> shapes;    

   shapes.push_back(std::make_shared<Circle>(1, 2, 3));
   shapes.push_back(std::make_shared<Rectangle>(4, 5, 6, 7));

   for (const auto& shape : shapes) 
   {
       shape->print();
       shape->draw();
       std::printf("Area: %f\n", shape->area());
   }

The output of the code will be:

.. code:: cpp

   Circle at (1.000000, 2.000000) with radius 3.000000
   Drawing Circle at (1.000000, 2.000000) with radius 3.000000
   Area: 28.274310
   Rectangle at (4.000000, 5.000000) with width 6.000000 and height 7.000000
   Drawing Rectangle at (4.000000, 5.000000) with width 6.000000 and height 7.000000
   Area: 42.000000

Here we can see that the **print()**, **draw()** and **area()** methods
of the **Shape** class are called for each object in the collection. The
**print()** method of the **Circle** and **Rectangle** classes are
called because they override the **print()** method of the **Shape**
class. The same goes for the **area()** and **draw()** methods.

.. note::

::

   Polymorphism only works for pointers and references to objects. If we use objects directly, the methods of the base class will be called.

`:fontawesome-solid-gears: Try
example <https://godbolt.org/z/jY43hsW1b>`__\ { .md-button
.target=“\_blank”}

Abstract classes
----------------

An abstract class is a class that can’t be instantiated. Abstract
classes are used to define a common interface for a group of classes.
The **Shape** class is an example of an abstract class. Our current
**Shape** class does not prevent it from being instatiated. To make the
**Shape** class abstract we need to add a pure virtual method to the
class. A pure virtual method is a method that has no implementation.
Pure virtual functions are defined by assigning then 0. The following
code shows how to make the **Shape** class abstract.

.. code:: cpp

   class Shape {
   public:
       ...
       virtual void print() const = 0;
       virtual double area() const = 0;
       virtual void draw() const = 0;
   };

When a class has a pure virtual method it can’t be instantiated. The
following code will produce a compiler error.

.. code:: cpp

   Shape s; // Error: Can't instantiate an abstract class
   std::unique_ptr<Shape> s = std::make_unique<Shape>(); // Error: Can't instantiate an abstract class

When deriving from a pure virtual class all pure virtual methods must be
implemented. The following code shows how to implement the **Shape**
class.

.. code:: cpp

   class Circle : public Shape {
   public:
       ...
       virtual void print() const override;
       virtual double area() const override;
       virtual void draw() const override;
   };

Composition
-----------

Composition is a way to combine objects to create more complex objects.
Composition is used when one object is part of another object. For
example, a **Car** object can be composed of **Wheel** objects. The
**Wheel** objects are part of the **Car** object. The following code
shows how to create a **Car** class that is composed of **Wheel**
objects.

.. code:: cpp

   class Wheel {
   public:
       Wheel() { std::printf("Wheel() constructor called.\n"); }
       ~Wheel() { std::printf("~Wheel() destructor called.\n"); }
   };

   class Car {
   private:
       Wheel m_wheels[4];
   public:
       Car() { std::printf("Car() constructor called.\n"); }
       ~Car() { std::printf("~Car() destructor called.\n"); }
   };

The following code shows how to create a **Car** object.

.. code:: cpp

   Car c;

The output of the code will be:

.. code:: cpp

   Wheel() constructor called.
   Wheel() constructor called.
   Wheel() constructor called.
   Wheel() constructor called.
   Car() constructor called.

When the **Car** object is destroyed the **Wheel** objects are also
destroyed. The following code shows how to destroy the **Car** object.

.. code:: cpp

   ~Car() destructor called.
   ~Wheel() destructor called.
   ~Wheel() destructor called.
   ~Wheel() destructor called.
   ~Wheel() destructor called.

`:fontawesome-solid-gears: Try
example <https://godbolt.org/z/xboGbPr1e>`__\ { .md-button
.target=“\_blank”}

Header and source files for classes
-----------------------------------

When working with classes it is common to split the class definition and
implementation into two files. The class definition is placed in a
header file with the extension **.h** or **.hpp**. The class
implementation is placed in a source file with the extension **.cpp**.
The following code shows how to split the **Shape** class into a header
and source file.

**shape.h**

This file contains the class definition for the **Shape** class. Usually
the header files don’t contain the implementation of the methods, only
the method signatures.

.. code:: cpp

   #ifndef SHAPE_H
   #define SHAPE_H

   #include <string>

   class Shape {
   private:
       double m_x{};
       double m_y{};
       double m_fillColor[4]{ 1.0, 0.0, 0.0, 1.0 };
       double m_lineColor[4]{ 0.0, 0.0, 0.0, 1.0 };
       std::string m_name{};
   public:
       Shape();
       Shape(double x, double y);
       
       void setPosition(double x, double y);
       double x() const;
       double y() const;

       void setFillColor(double r, double g, double b, double a);
       void setLineColor(double r, double g, double b, double a);

       void getFillColor(double& r, double& g, double& b, double& a) const;
       void getLineColor(double& r, double& g, double& b, double& a) const;

       void setName(const std::string& name);
       std::string name() const;

       virtual void print() const;
       virtual double area() const;
       virtual void draw() const;
   };

   #endif

The **#ifndef**, **#define** and **#endif** directives are used to
prevent the header file from being included multiple times in the same
file. This is called an include guard.

**shape.cpp**

This file contains the implementation of the **Shape** class. The first
part of this file is the include directive for the **shape.h** file.
This is done to make sure that the class definition is available when
the implementation is compiled.

.. code:: cpp

   #include "shape.h"

   Shape::Shape()
   {}

   Shape::Shape(double x, double y)
       : m_x{x}, m_y{y}
   {}

   void Shape::setPosition(double x, double y)
   {
       m_x = x;
       m_y = y;
   }

   double Shape::x() const
   {
       return m_x;
   }

   double Shape::y() const
   {
       return m_y;
   }

   void Shape::setFillColor(double r, double g, double b, double a)
   {
       m_fillColor[0] = r;
       m_fillColor[1] = g;
       m_fillColor[2] = b;
       m_fillColor[3] = a;
   }

   void Shape::setLineColor(double r, double g, double b, double a)
   {
       m_lineColor[0] = r;
       m_lineColor[1] = g;
       m_lineColor[2] = b;
       m_lineColor[3] = a;
   }

   void Shape::getFillColor(double& r, double& g, double& b, double& a) const
   {
       r = m_fillColor[0];
       g = m_fillColor[1];
       b = m_fillColor[2];
       a = m_fillColor[3];
   }

   void Shape::getLineColor(double& r, double& g, double& b, double& a) const
   {
       r = m_lineColor[0];
       g = m_lineColor[1];
       b = m_lineColor[2];
       a = m_lineColor[3];
   }

   void Shape::setName(const std::string& name)
   {
       m_name = name;
   }

   std::string Shape::name() const
   {
       return m_name;
   }

   void Shape::print() const
   {
       std::printf("Shape: %s\n", m_name.c_str());
       std::printf("Position: (%f, %f)\n", m_x, m_y);
   }

   double Shape::area() const
   {
       return 0.0;
   }

   void Shape::draw() const
   {
       std::printf("Drawing shape at: (%f, %f)\n", m_x, m_y);
   }

Using this method of splitting the class definition and implementation
into two files makes it easier to manage large projects. It also makes
it easier to reuse classes in other projects.

Alternatives to header guards
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

An alternative to using include guards is to use the **#pragma once**
directive. The **#pragma once** directive tells the compiler to only
include the file once. The following code shows how to use the **#pragma
once** directive.

.. code:: cpp

   #pragma once

   #include <string>

   class Shape {  
       ...
   };

The **#pragma once** directive is supported by most modern compilers and
is a more modern way of preventing multiple inclusions of the same file.

Object-oriented analysis
------------------------

Object-oriented analysis is the process of defining the objects and
their relationships in a system. The goal of object-oriented analysis is
to identify the objects in a system and how they interact with each
other. The following steps are used in object-oriented analysis:

1. Identify the objects in the system
2. Identify the relationships between the objects
3. Identify the attributes of the objects

The following example shows how to perform object-oriented analysis on a
simple system.

Implementing a graphics library
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

As an example a simple graphics library will be implemented. The library
will be able to draw shapes on the screen. The following objects are
identified in the system:

- **Shape** - The base class for all shapes
- **Circle** - A circle shape
- **Rectangle** - A rectangle shape
- **Line** - A line shape
- **Text** - A text shape
- **Composite** - A composite shape
- **Canvas** - The canvas where the shapes are drawn
- **Color** - A color object
- **Point** - A point object
- **Font** - A font object
- **Pen** - A pen object
- **Brush** - A brush object

The relationships between the objects are:

- **Circle**, **Rectangle**, **Line**, **Text** - Inherit from **Shape**
- **Composite** - Contains a list of **Shape** objects
- **Canvas** - Contains a list of **Shape** objects

The attributes of the objects are:

- **Shape** - Position, fill color, line color
- **Circle** - Radius
- **Rectangle** - Width, height
- **Line** - Start point, end point
- **Text** - Text, font
- **Composite** - List of shapes
- **Canvas** - List of shapes
- **Color** - Red, green, blue, alpha
- **Point** - X, Y
- **Font** - Name, size
- **Pen** - Color, width
- **Brush** - Color

We now have the base for our graphics library. The next step is to
implement the classes and their relationships.

Object-oriented design of a particle system
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

As an example a simple particle system will be implemented. The particle
system will be able to simulate particles moving in a 2D space. The
following objects are identified in the system:

- **Vector** - A 2D Vector class
- **BaseParticle** - The base class for all particles types
- **Particle** - A particle object
- **ParticleSystem** - The particle system that contains the particles
- **Emitter** - An emitter that emits particles
- **Attractor** - An attractor that attracts particles
- **Repeller** - A repeller that repels particles
- **Boundary** - A boundary that contains the particles

The relationships between the objects are:

- **BaseParticle** - Inherit from **Point**
- **Particle** - Inherit from **BaseParticle**
- **Particle** and **BaseParticle** - Uses Vector for position,
  velocity, and acceleration
- **ParticleSystem** - Contains a list of **Particle** objects
- **Emitter** - Creates **Particle** objects
- **Attractor** - Attracts **Particle** objects
- **Repeller** - Repels **Particle** objects
- **Boundary** - Constrains **Particle** objects

The attributes of the objects are:

- **Point** - X, Y
- **BaseParticle** - Position, velocity, acceleration, mass
- **Particle** - Lifetime, color
- **ParticleSystem** - List of particles
- **Emitter** - Position, emission rate
- **Attractor** - Position, strength
- **Repeller** - Position, strength
- **Boundary** - Position, width, height

We now have the base for our particle system. The next step is to
implement the classes and their relationships.

The following code shows an example of how the classes could be
implemented.

.. code:: cpp

   class Vector {
   private:
       double m_x;
       double m_y;
   public:
       Vector(double x, double y)
           : m_x(x), m_y(y)
       {}

       double x() const { return m_x; }
       double y() const { return m_y; }

       void setX(double x) { m_x = x; }
       void setY(double y) { m_y = y; }

       void move(double dx, double dy) { m_x += dx; m_y += dy; }
   };

   class BaseParticle {
   private:
       Vector m_position;
       Vector m_velocity;
       Vector m_acceleration;
       double m_mass;
   public:
       BaseParticle();
       BaseParticle(const Vector& position, const Vector& velocity, const Vector& acceleration, double mass);
       
       void setPosition(const Vector& position);
       Vector position() const;
       
       void setVelocity(const Vector& velocity);
       Vector velocity() const;
       
       void setAcceleration(const Vector& acceleration);
       Vector acceleration() const;
       
       void setMass(double mass);
       double mass() const;

       void move();
       void applyForce(const Vector& force);
   };

   class Particle : public BaseParticle {
   private:
       double m_lifetime;
       Color m_color;
   public:
       Particle();
       Particle(const Vector& position, const Vector& velocity, const Vector& acceleration, double mass, double lifetime, const Color& color);
       
       void setLifetime(double lifetime);
       double lifetime() const;
       
       void setColor(const Color& color);
       Color color() const;
   };

   using ParticlePtr = std::shared_ptr<Particle>;

   class ParticleSystem {
   private:
       std::vector<ParticlePtr> m_particles;
   public:
       ParticleSystem();
       
       void addParticle(const ParticlePtr& particle);
       void removeParticle(const ParticlePtr& particle);
       
       void update();
       void draw();
   };

   class Emitter {
   private:
       Vector m_position;
       double m_emissionRate;
   public:
       Emitter(const Vector& position, double emissionRate);
       
       void setPosition(const Vector& position);
       Vector position() const;
       
       void setEmissionRate(double emissionRate);
       double emissionRate() const;
       
       ParticlePtr emit();
   };

   class Attractor {
   private:
       Vector m_position;
       double m_strength;
   public:
       Attractor(const Vector& position, double strength);
       
       void setPosition(const Vector& position);
       Vector position() const;
       
       void setStrength(double strength);
       double strength() const;
       
       Vector force(const ParticlePtr& particle) const;
   };

   class Repeller {
   private:
       Vector m_position;
       double m_strength;
   public:
       Repeller(const Vector& position, double strength);
       
       void setPosition(const Vector& position);
       Vector position() const;
       
       void setStrength(double strength);
       double strength() const;
       
       Vector force(const ParticlePtr& particle) const;
   };

   class Boundary {
   private:
       Vector m_position;
       double m_width;
       double m_height;
   public:
       Boundary(const Vector& position, double width, double height);
       
       void setPosition(const Vector& position);
       Vector position() const;
       
       void setWidth(double width);
       double width() const;
       
       void setHeight(double height);
       double height() const;
       
       void constrain(ParticlePtr& particle);
   };

Comments on object-oriented analysis
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Object-oriented analysis is a powerful tool for designing complex
systems. By identifying the objects in a system and how they interact
with each other, we can create a clear and concise design.
Object-oriented analysis is used in many fields, including software
development, engineering, and business. By using object-oriented
analysis, we can create systems that are easy to understand, maintain,
and extend.

When using object-oriented analysis in computation science it is also
important to consider the performance of the system. Object-oriented
programming can introduce overhead in terms of memory and processing
time. It is important to consider the trade-offs between performance and
maintainability when designing a system.

In the previous example the **Particle** class was instantiated in a
**std::vector** and every particle allocated on the heap. This design
can lead to performance issues when the number of particles is large. An
alternative approach would be to implement a **Particles** class that
implements a fixed-size array of particles. This would reduce the
overhead of memory allocation and deallocation and improve performance.
It is also possible to use a memory pool to allocate and deallocate
particles more efficiently.
