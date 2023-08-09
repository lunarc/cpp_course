# Organising your code

 * C++ does not have any concept of modules of code
 * Compiler “sees” only one single block of text
 * Preprocessor handles code structuring
 * `#include` directive includes external source files for consideration when compiling
 * Header files – Files containing function prototypes for used libraries
   * `#include <filename>` include file in standard locations
   * `#include "filename"` include file relative to compiled source code

## The C++ compilation and linking

 1. Source files are combined with header files to source units.
 2. The compiler compiles each source unit to an object file.
 3. Object files are linked together to form applications or shared libraries by the linker.

## Code module in C++

 * A module in C++ is usually defined by a 
   * header file (.h)
   * source file (.cpp)
 * Header file contains functions and class definitions
 * Source file contains the actual functions
 * Problem: How do you handle headers used in multiple source files – duplicate function prototypes

## Headers and source files

=== "Using header guards"

    Header file - array_utils.h

    ``` cpp
    --8<-- "../ch_functions/array_utils.h"
    ```

    Source file - header_files.cpp

    ``` cpp
    --8<-- "../ch_functions/header_files.cpp"
    ```

=== "Using pragma once"

    Header file - array_utils2.h

    ``` cpp
    --8<-- "../ch_functions/array_utils2.h"
    ```

    Source file - header_files2.cpp

    ``` cpp
    --8<-- "../ch_functions/header_files2.cpp"
    ```

## pragma once

 * non-standard widely supported preprocessor directive
 * Can be used to replace header guards
 * Less code
 * avoids name clashes
 * improved compile speed




