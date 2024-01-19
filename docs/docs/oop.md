# Object-oriented programming

In procedural programming, data and subroutines are treated separately. Subroutines operate on provided data structures and variables. In object-oriented programming data and subroutines are combined into objects. Objects in numerical computing can be different matrix types, particles, vectors or solvers. The major benefits are that the actual data structures used in the implementation of an object can be hidden from the user of the object, enabling the developer of an object to improve the implementation without affecting users of the objects (encapsulation). Another important feature of object-oriented programming is the ability to inherit and extend functionality of objects (inheritance). This enables user of object and developers to extend and modify functionality of existing objects, relying on functionality of the parent object.

The functionality and data structures of objects are defined in classes in most programming object-oriented languages. Classes can be seen as templates or blueprints for objects. When an object is to be created the class is used as the template to construct the new object. Created objects are also called instances of a class.

* Normal programs can be seen as a number of tasks/functions to perform. 
* An object oriented program can be seen as a number of interacting objects
* Objects can receive messages, process data, send messages to other objects
* Objects hide data from view. Access through methods
* Object-oriented can be traced back to Simula 67

Key features

* Dynamic dispatch (late binding)
  - Actual method called is determined at runtime
  - Enabled Polymorphism
* Polymorphism
  - Several objects sharing characteristics
  - Shape – Circle, Rectangle, Oval
* Encapsulation
  - Combine data and function in a single entity
  - Restricting access to actual data
* Inheritance
  - Reuse code of an existing object/classes
  - Inherit attributes from an existing classes

## Classes in C++

C++ introduces the concept of a class

A class can be seen as a struct which contain functions for accessing data

Variables and methods of a class can be 

* private – Not accessible by derived classes and from instance.
* protected – Accessible by derived classes but not from instance.
* public – Accessible by derived classes and from instance

A class is a blueprint for an instance or object

An instance can be created on the stack or on the heap using the new operator

A Class often represents a noun such as a person, particle, shape

## Declaring classes in C++

## Instantiating classes

## Object-oriented analysis

Object relationships

* has – A car has wheels (aggregation)
* has – A particle system has particles (composite)
* is – A Triangle is a Shape (specialisation inheritance)


