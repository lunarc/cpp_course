Mixed-language programming
==========================

.. image:: images/mixed-language.png
   :width: 100.0%

It is not always possible to reimplement applications in the language of choice. You have proven libraries or code written in C and Fortran that you don't want to or is required to rewrite in C++.In many cases it can also be advantagous to provide ways of integrating your C++ code with languages such as Python, providing users with an easy access to it. In these situations you need to know how combine code written in different languages, a concept called mixed-language programming. 

In this chapter we will go through some common scenarios, best practices and tools that can be helpful. Focus will be on interfacing Python with C++, which is one of the most important use cases and perhaps also the most complex use case as Python is a dynamic interpreted language.

.. - Motivation: Why mix languages (leverage existing libraries, performance, prototyping)
.. - Overview of common scenarios in scientific computing
.. - General principles: ABI compatibility, data marshalling, memory management

Interfacing with C
------------------

Perhaps the easiest language to integrate into C++ is C because of it close relationship and synchronised development. However, there are some caveats and thinks to think about when mixing the languages.

The C++ and C Relationship
~~~~~~~~~~~~~~~~~~~~~~~~~~

Even though C and C++ are closely related there are some issues. First when compiling C/C++ code the compiler will give names (name mangling or name decoration) to the functions that can be used by the linker to identify the functions later when linking the code or to identify functions in libraries. C++ has a different naming scheme than C to be able support additional features such as namespaces, function overloading and templates. This means that it is not directly possible to link C and C++ code. To solve this the C++ compiler uses a specific compiler linkage instruction, ``extern "C"``, to indicate that a symbol should use C name mangling. In the following code the function myfunc will be declared using C name mangling.

.. code:: cpp

   extern "C" void myfunc(int x, int y);

When linking the code the function reference will be stored using the C name mangling scheme and linked to the correct C function.

It is also possible to define several functions using a block declaration variant of ``extern "C"``.

.. code:: cpp

   extern "C" {
      void function1(int x);
      void function2(double y);
      int function3(char* str);
   }

Calling C functions from C++
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The name mangling can become a problem if you have C library implemented without any specific C++ adjustments. To be able to call the library from C++ you can surround the include statement with the ``extern "C"`` linkage instruction. Suppose you have a library with the following header:

.. code:: C

   #ifndef MATH_UTILS_H
   #define MATH_UTILS_H

   double integrate_simpson(double (*f)(double), double a, double b, int n);
   void matrix_multiply(const double* A, const double* B, double* C, 
                        int m, int n, int p);

   #endif   

This library can be used in a C++ code using the following code:

.. code:: cpp

   // Include our C library using extern "C"

   extern "C" {
   #include "math_utils.h"
   }

   #include <cmath>

   double my_function(double x) 
   {
      return std::exp(-x * x);
   }

   int main() 
   {
      // Call C function with C++ function pointer
   
      double result = integrate_simpson(my_function, 0.0, 1.0, 1000);
      
      // Call C matrix function
   
      double A[4] = {1.0, 2.0, 3.0, 4.0};
      double B[4] = {5.0, 6.0, 7.0, 8.0};
      double C[4];
      matrix_multiply(A, B, C, 2, 2, 2);
      
      return 0;
   }

Header compatibility
~~~~~~~~~~~~~~~~~~~~

In many cases using C libraries will not be an issue as many of these already already wrapped in ``extern "C"`` linkage instructions. However it can be good to understand how you should implement C headers that can be used for both C and C++. 

If you need to adapt a C library to be able to be directly included and linked in a C++ project the is a special preprocessor definition, ``__cplusplus`` you can use to check if the header is being compiled with a C++ compiler and include required linkage instructions. We can modify our C math library in the previous example to be directly used in C++ by adding some preprocessor code as shown below:

.. code:: C

   #ifndef MATH_UTILS_H
   #define MATH_UTILS_H

   // Check if included from a C++ compiler (add extern "C")

   #ifdef __cplusplus
   extern "C" {
   #endif

   double integrate_simpson(double (*f)(double), double a, double b, int n);
   void matrix_multiply(const double* A, const double* B, double* C, 
                        int m, int n, int p);

   #ifdef __cplusplus
   }
   #endif

   #endif   

Exposing C++ libraries to C
~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you want to expose C++ libraries to C++ the situation becomes a bit trickier as the C is a subset of C++ and doesn't contain the same functionality. To solve this you need to provide a specific C interface that exposes the C++ functionality in C functions. 

Consider the following C++ class header

.. code:: cpp

   #pragma once

   #include <vector>
   #include <cmath>

   class Point {
      double m_, m_y;
   public:
      Point(double x, double y) : m_x{x}, m_y{y} {}
      double distance_to(const Point& other) const;
   };

and implementation.

.. code:: cpp

   #include "point.h"

   double Point::distance_to(const Point& other) const {
      double dx = m_x - other.m_x;
      double dy = m_y - other.m_y;
      return std::sqrt(dx * dx + dy * dy);
   }

If we want to make this class available to use from C we need to make some adjustments to the header and source implementation. For C we need to create a specific function oriented library that internally creates an instance and returns a pointer to the instance. We use the ``__cplusplus`` define to hide the class declaration and expose our C based API in the header.

.. code:: cpp

   #pragma once

   // Hide the class declaration from C

   #ifdef __cplusplus

   #include <vector>
   #include <cmath>

   class Point {
      double x_, y_;
   public:
      Point(double x, double y) : x_(x), y_(y) {}
      double distance_to(const Point& other) const;
   };

   #endif

   // C-compatible wrapper

   #ifdef __cplusplus
   extern "C" {
   #endif

   // Opaque handle for C code
   typedef void* PointHandle;
      
   // Creates a point instance and returns a pointer
   PointHandle point_create(double x, double y); 

   // Destroys a point instance from a pointer
   void point_destroy(PointHandle handle);       

   // Calls the distance_to method on a Point instance
   double point_distance(PointHandle p1, PointHandle p2);

   #ifdef __cplusplus 
   }
   #endif   

The implementation file will be compiled with a C++ compiler, but we must provide the C functions using the correct name mangling using the ``extern "C"``. The implementation file is shown below.

.. code:: cpp

   #include "point.h"

   double Point::distance_to(const Point& other) const 
   {
      double dx = m_x - other.m_x;
      double dy = m_y - other.m_y;
      return std::sqrt(dx * dx + dy * dy);
   }

   extern "C" {
      
   PointHandle point_create(double x, double y) {
      return new Point(x, y);
   }

   void point_destroy(PointHandle handle) {
      delete static_cast<Point*>(handle);
   }

   double point_distance(PointHandle p1, PointHandle p2) {
      Point* point1 = static_cast<Point*>(p1);
      Point* point2 = static_cast<Point*>(p2);
      return point1->distance_to(*point2);
   }

   }
  
Common Pitfalls
~~~~~~~~~~~~~~~

There are some things to think about when exposing C++ libraries to C. Exceptions cannot be exposed to C, so exception handling must be done in the exposed C API implementation. This could be done using specific API calls or return values from functions. An example of this is shown in the following function:

.. code:: cpp

   extern "C" int safe_divide(int a, int b, int* result) 
   {
       try {
           if (b == 0) throw std::runtime_error("Division by zero");
           *result = a / b;
           return 0;  // success
       } catch (...) {
           return -1;  // error
       }
   }

Here we catch the exception internally to the C++ implementation and return error status through a return value.

Another important aspect is memory management. Who is responsible for allocating memory and deallocating memory. There needs to be a clear ownership defined in the exposed API. In the previous Point class API we defined clear functions ``point_create()`` and ``point_destroy()`` for handling allocation and destruction. This makes it clear for any users of the library that they are responsible for destroying the created objects. There is also no smart pointer mechanism for guaranteeing destruction of allocated objects.

Most common datatypes including structs are compatible with C, however one should be a bit careful with struct padding and alignment.

Interfacing with Python (Python C API)
--------------------------------------

Python is becoming a more and more important language within the scientific community due to it's ease of use and multitude of available libraries. Many of the large AI frameworks such as PyTorch and Tensorflow are implemented in C++ but the main access is through a Python based API. 

There are many reasons for using C++ in combination with Python. One reason can be that performance of pure Python code doesn't even come close to the performance of C++ code. By implementing performance critical code in C++ you can accelerate your Python code significantly. Another reason could be to provide access to existing C++ library for use with Python. For graphical applications it is also possible to embed Python as an internal scripting language enabling users to automate and adapt the application. In this section we will mainly discuss how to expose C++ code as modules in Python.

Extending Python
~~~~~~~~~~~~~~~~

Extending Python is done by implementing a special shared library or dll containing special exposed functions that Python will call to enumarate the functions and to call the extended function. To create and use built-in Python data types the library must be linked with the ``libpython`` library that contains the function to interface with Python. In the next section we will implement a very simple extension module using the Python C API.

A very simple math extension
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In the first step we will create a C++ source file which is going to contain the functions implementing the extension module. To build a Python module we need some defintions and includes.

.. code:: cpp

   #define PY_SSIZE_T_CLEAN 
   #include <Python.h>

The define is required to define modern behavior of index and size arguments. We don't use it in our example, but it is best practice. The ``<Python.h>`` header defines the function of the Python C API we are going to use to implement the module.

Next, we are going to implement a simple factorial function using this API. The function must be declared using only API datatypes, so the factorial function definition becomes:

.. code:: cpp

   static PyObject* mathext_factorial(PyObject* self, PyObject* args)

The most important data type in the Python C API is the ``PyObject`` it is the base object of all data types. We will use these object for extracting the information we need for our function. The first step we have to do in the function is to parse the incoming arguments in the ``args`` object with the ``PyArg_ParseTuple()`` function to make sure we have the correct arguments. We exit and return ``NULL`` if the function returned ``false``. We also declare a variable ``n``, which we will use to store the incoming argument.

.. code:: cpp

   int n;

   // Parse arguments - expects one integer 

   if (!PyArg_ParseTuple(args, "i", &n)) 
   {
      return NULL;  // Exception already set by PyArg_ParseTuple
   }   

We then check if ``n<0`` as n has to be non-negative to be able to calculate the factorial. We can the use the ``PyErr_SetString()`` function to generate a ``ValueError`` exception with a given string. 

.. code:: cpp

    // Input validation

    if (n < 0) 
    {
        PyErr_SetString(PyExc_ValueError, "Factorial requires non-negative integer");
        return NULL;
    }   

Now we have all we need to do our actual calculation we check for overflow and use the error function again to generate a ``OverflowError`` exception.

.. code:: cpp

    // Calculate factorial 

    long long result = 1;
    for (int i = 2; i <= n; i++) 
    {
        result *= i;

        // Check for overflow 

        if (result < 0) 
        {
            PyErr_SetString(PyExc_OverflowError, "Factorial result too large");
            return NULL;
        }
    }   

In the final step we need to create a ``PyObject`` for our return value. This is done by using the function ``PyLong_FromLongLong``

.. code:: cpp

      /* Return result as Python integer */
      return PyLong_FromLongLong(result);
   }

There are three more things we need to implement before we can compile our extension module. 

1. Implement a method definition table.
2. Implement a module definition structure.
3. Provide a module initialisation function.

In the method definition table we define what the functions are going to be named in Python, what C++ function that is implementing it and a documentation string describing the function. As we only have a single function the definition table then becomes:

.. code:: cpp

   // Method definition table

   static PyMethodDef MathExtMethods[] = {
      {
         "factorial",                    // Method name in Python 
         mathext_factorial,              // C function 
         METH_VARARGS,                   // Accepts positional arguments 
         "Calculate factorial of n"      // Docstring 
      },
      {NULL, NULL, 0, NULL}  // Sentinel 
   };   

If you have more functions you list them before the ``{NULL, NULL, 0, NULL}`` sentinel mark.

Next, we do a similar structure that defines the module. We give the module a name, a documentation string and our method definition table.

.. code:: cpp

   // Module definition structure 
   static struct PyModuleDef mathextmodule = {
      PyModuleDef_HEAD_INIT,
      "mathextsimple",                    // Module name 
      "Simple math extension module",     // Module docstring 
      -1,                                 // Module state size (-1 = no state) 
      MathExtMethods
   };

The final step is to provide a module initialisation function. This function is called by Python when the module is imported and is responsible to create the module and associated functions. It is basically a function with a single function call that takes our module definition as input.

.. code:: cpp

   // Module initialization function - must be named PyInit_<modulename> 
   PyMODINIT_FUNC PyInit_mathextsimple(void) {
      return PyModule_Create(&mathextmodule);
   }   

To build the function we need to define a setup definition in Python that gives some additional instructions on how to compile the module using the Python build tools. In the definition we instantiate an ``Extension`` object, ``ext``, with some attributes which we give as argument to the ``setup()`` method from the ``setuptools`` module. The complete definition is shown below:

.. code:: python

   from setuptools import setup, Extension

   ext = Extension(
      'mathextsimple',
      sources=['mathextsimple.cpp'],
      language='c++',
      extra_compile_args=['-std=c++17'],
   )

   setup(
      name='mathextsimple',
      ext_modules=[ext],
   )   

The important arguements to the ``Extension`` constructor is:

* Name of the the module.
* sources - list of sources that compiles the extension module.
* language - what compiler to use to compile the extension module.
* extra_compile_args - any additional compiler flags used when compiling the module.

The module is the compiled using the following commands:

.. code:: 

   python mathext_build.py build_ext --inplace

This will build and will produce the file ``mathextsimple.cp312-win_amd65.pyd`` on windows and a similar file with the extension ``.so`` on a Linux system.

We can test the function by running the following Python script:

.. code:: python

   import mathextsimple
   
   print(mathextsimple.factorial(5))

This will print 120, which should be correct.

We can clearly see here that is a somewhat complicated and error prone process to create extension modules manually using the Python C API. In the next chapter we are going to use the power of C++ to make the process of implementing Python modules much easier. It is also what the rest of this Python chapter will focus on.
  
Interfacing with Python using Pybind11
--------------------------------------

Pybind11 is a headerless library that can expose C++ datatypes in Python and in the other direction as well. Let's start by implementing our factorial example using Pybind11 instead. 

First, we start by including the following header:

.. code:: cpp

   #include <pybind11/pybind11.h>

Now we just implement our factorial function using normal C++. No need for any special Python API calls.

.. code:: cpp

   long long factorial(int n) 
   {
      if (n < 0) 
      {
         throw std::invalid_argument("Factorial requires non-negative integer");
      }

      long long result = 1;
      for (int i = 2; i <= n; i++) 
      {
         result *= i;
         
         // Check for overflow

         if (result < 0) 
         {
               throw std::overflow_error("Factorial result too large");
               return NULL;
         }
      }

      return result;
   }   

The real magic happens at the end. Here we call the Pybind11 macro ``PYBIND11_MODULE`` which is responsible for generating the required binding code. The first argument of the macro is the module name and the second defines a variable of the type ``py::module_`` which is the interface we will use to define what goes into the module. For our factorial math module the code becomes:

.. code:: cpp

   PYBIND11_MODULE(mathextsimple_pb, m) {
      m.def("factorial", &factorial, "Calculate factorial of n");
   }   

Compiling it is done in almost the same way. We create a python setup definition again. This time we add some Pybind11 specific functionality.

.. code:: python

   from setuptools import setup, Extension
   import pybind11

   ext = Extension(
      'mathextsimple_pb',
      sources=['mathextsimple_pb.cpp'],
      include_dirs=[pybind11.get_include()],
      language='c++',
      extra_compile_args=['-std=c++17'],
   )

   setup(
      name='mathextsimple_pb',
      ext_modules=[ext],
   )   

In the definition we have added an import of the ``pybind11`` module, which will enable us to specify where the compiler can find the include files for Pybind11 using the ``pybind11.get_include()`` function.

A simple math extension again (Pybind11)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~