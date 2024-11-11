Organising your code
====================

Modern C++ has introduced the concept of modules just like Fortran and
Python. However, using C++ modules currently is problematic as different
compiler vendors have implemented this is different ways. The current
recommended way of organising C++ code is to use header files and source
files. A headed file is a file containing function, class and type
declarations. The source files contain the actual implementation of the
items declared in the header file.

The compiler sees only one single block of text. To be able to organise
code in C++ a special tool called a preproessor is used. The
``#include`` statement is such a preprocessor directive that includes
external source files for consideration when compiling. Include files in
C++ usually have the suffix ``.h`` or ``.hpp``. The
``#include <filename>`` directive includes a file in standard locations,
while the ``#include "filename"`` directive includes a file relative to
the compiled source code.

Compilation and linking in C++
------------------------------

The C++ compilation and linking process is a three-step process:

1. Source files are combined with header files to source units.
2. The compiler compiles each source unit to an object file.
3. Object files are linked together to form applications or shared
   libraries by the linker.

There are of course many additional steps in the actual compilation, but
these are the main high-level steps.

Code units in C++ (.h/.cpp)
---------------------------

To organise your application or library, divide your code into logical
units. Each unit should have a clear interface (.h) defining related
functions, declaration, enums and classes. Try to avoid having too much
functionality in a single unit.

A unit in C++ is usually defined by a header file (.h) and a source file
(.cpp). The header file contains function and class declarations, while
the source file contains the actual implementation of the functions and
classes declared in the header file.

A problem arises when using the #include directive. If you include a
header file in multiple source files, the compiler will see the same
code multiple times. This can lead to multiple definition errors. To
avoid this, you can use a concept called header guards. There are 2 type
of header guards.

The first is using ``#ifndef``, ``#define`` and ``#endif`` preprocessor
directives. In this concept when an include file is includes a check is
done for a unique identifier for this include file. If not found the
include file has not yet been included. We then set the unique
identifier. Next time the file is included the unique identifier is
found and the content of the include file will not be processed.

The second approach is using ``#pragma once`` preprocessor directive.
The ``#pragma once`` directive is a non-standard but widely supported
preprocessor directive that can be used to replace header guards. It is
less code, avoids name clashes and improves compile speed.

The following example shows how to use header guards and pragma once.

.. tabs::

   .. tab:: Using header guards
      .. literalinclude:: ../../ch_functions/array_utils.h

      Source file - header_files.cpp

      .. literalinclude:: ../../ch_functions/header_files.cpp

   .. tab:: Source file - header_files.cpp
      .. literalinclude:: ../../ch_functions/array_utils2.h

      Source file - header_files.cpp

      .. literalinclude:: ../../ch_functions/header_files2.cpp


