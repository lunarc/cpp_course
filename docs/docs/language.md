# Language elements

## Example of C++ code

``` cpp
--8<-- "../hello_world/hello.cpp"
```

``` cpp
--8<-- "index.md"
```

## Variable names

* Letters a-z, A-Z (not Å, Ä, Ö) 
* Numbers 0-9 
* Underscore _ 
* First character must be a letter
* Lower case letters are not equivalent with upper case letters. Case sensitive language

## Variable types

| Type   | Description          |
|--------|----------------------|
| bool   | boolean type         |
| char   | character type       |
| int    | integer numbers      |
| double | floating point type  |
| float  | floatiung point type |
| long   | integer type         |

* Most basic types are available in different flavors

  * size
  * unsigned / signed

* Sizes of variables types depend on platform and compiler

## Integer types
-------------

* Integer

  * basic type – int (signed)
  * short int, int and long int
  * unsigned and signed  
  * Short forms: long, short, int

* Don’t use unsigned to prevent negative values

  * Problems in conversions later

* Use unsigned to represent bit patterns

``` cpp
--8<-- "../ch_variables/int_types1.cpp"
```

### Code output

    a = -1
    b = 4294967295
    c = -1
    d = 18446744073709551615

### Size of integer types

* Depends on compiler and platform
* Actual size can be determined by sizeof operator
* returns size measured in sizeof(char) = 1
* 1 = sizeof(char) ≤ sizeof(short) ≤ sizeof(int) ≤ sizeof(long)
* 1 ≤ sizeof(bool) ≤ sizeof(long)
* sizeof(char) ≤ sizeof(wchar_t) ≤ sizeof(long)
* sizeof(float) ≤ sizeof(double) ≤ sizeof(long double)
* sizeof(N) = sizeof(signed N) = sizeof(unsigned N)

``` cpp
--8<-- "../ch_variables/int_types2.cpp"
```

### Code output

    a = -1, sizeof(a) = 4
    b = 4294967295, sizeof(b) = 4
    c = -1, sizeof(c) = 8
    d = 18446744073709551615, sizeof(d) = 8

## Character types

* represents a character in the implementation character set
* 8-bits on most systems
* Character sets often guaranteed to contain numeric characters, 26 letters of the english alphabet and common delimiters
* Check implementation
* signed char -128..127
* unsigned char 0..255
* char is dependent on implementation
* int(c) can return both variants


``` cpp
--8<-- "../ch_variables/char_types1.cpp"
```

Code output:

    c = a int(c) = 97 sizeof(c) = 1
    uc = \201 int(uc) = 129 sizeof(c) = 1
    sc = \202 int(sc) = -126 sizeof(c) = 1

## Floating point types

* float – single precision
* double – double precision 
* long double – extended precision
* Actual size depends on hardware and compiler
* use double if unsure
* Long double can be inefficient due to processor architecture

``` cpp
--8<-- "../ch_variables/double_types1.cpp"
```

Code output:

    f = 3.14159274101257
    d = 3.14159265358979
    ld = 3.14159265358979

## Numerical limits

* Use header file #include <limits>
* Can return platform data type limits
* General use:

  * numeric_limit<datatype>::max()
  * numeric_limit<datatype>::min()
  * numeric_limit<datatype>::is_signed()


### Example

``` cpp
--8<-- "../ch_variables/numerical_limits.cpp"
```

### Code output

    Max, char 127
    Min, char -128
    Is char signed 1
    Max, unsigned char 255
    Min, unsigned char 0
    Max, short 32767
    Min, short -32768
    Max, int 2147483647
    Min, int -2147483648
    Max, long 9223372036854775807
    Min, long -9223372036854775808
    Max, float 3.40282e+38
    Min, float 1.17549e-38
    Max, double 1.79769e+308
    Min, double 2.22507e-308
    Max, long double 1.18973e+4932
    Min, long double 3.3621e-4932

## Enumeration types

* Defines different kinds of enumerations
* Can be used as an integer type
* By default enumeration constants are given integer values in the order they are defined
* Specific values can be given to the enumeration constants.
* An enumeration can be a distinct data type.
* Converted to integers in expressions

### Example

``` cpp
--8<-- "../ch_variables/enum_types.cpp"
```

## Arrays

* “List of elements with a specific data type”
* Indexed from 0 … size - 1
* Brackets [ ] is used for accessing individual elements
* Declaration

  * [data type] name[size] [ = { list of values} ]

* Contigous multidimensional array not supported with indices. Tricks and OO can solve this 

### Example

``` cpp
--8<-- "../ch_variables/array_types1.cpp"
```

### Code output

    1, 2
    1, 2, 3, 42
    
## Pointers

* Declared with the * operator
* Can be typed and untyped (void*)
* Declaration

  * [data type]* name

* Pointer variable contains a memory address
* * operator is also used to dereference pointer and retrieve value at memory location
* & operator can be used to return a memory address for a non-pointer variable. 


### Example

``` cpp
--8<-- "../ch_variables/pointers1.cpp"
```

## Code output

    a = 42
    b = 0x7fff5fbff6bc
    &a = 0x7fff5fbff6bc
    *b = 42

<img src="../images/pointers1.svg" width="50%">

<img src="../images/pointers1-2.svg" width="50%">

\*b is the value stored at memory location b 

## Array pointer duality

* Array and pointers are very related in C/C++
* Pointer types can be accessed using array notation
* Arrays can be accessed like pointers
* Increases flexibility in algorithm design
* Increases risk of errors as well


### Example

``` cpp
--8<-- "../ch_variables/pointers2.cpp"
```

### Code output

    a = 0x7fff5fbff6a0
    b = 0x7fff5fbff6a0
    a[0] = 0
    b[0] = 0
    *b = 0
    *a = 0
    c = 0x7fff5fbff6a8
    *c = 2


<img src="../images/pointers1-3.svg" width="50%">


## Constants

* A way of defining data that is not changed during program execution
* Use instead of numeric constants in the code

  * Easier to update code in a later stage

* Prevents accidental modification of variables
* Gives hints to the compiler on optmisations

  * Precomputing expressions at compile time
  * Reduce memory usage

### Example

``` cpp
--8<-- "../ch_variables/const_types.cpp"
```

## References

* Alternative names for a variables
* Mainly used in function arguments
* [data type]& name

  * Defines a reference to another variable of the same data type

### Example

``` cpp
--8<-- "../ch_variables/reference_type.cpp"
```

### Code output

    a = 42
    b = 42
    &a = 0x7fff5fbff6bc
    &b = 0x7fff5fbff6bc

* b points to the same memory location as a

* b can be used as a normal variable after it has been initialised 

## Structured data types

* Data type consisting of a mix of other data types
* Compare entries in a database

  * first name
  * last name
  * street
  * ...
  
* Declared using the struct keyword
* Members are accessed with . (dot) or -> operators


### Example

``` cpp
--8<-- "../ch_variables/structured_type.cpp"
```

### Code output

    c1.x = 0, c1.y = 0
    c2.x = 1, c2.y = 1
    sizeof(c1) = 16

# Expressions and operators

## Arithmetic operators

| Operator | Description         |
|----------|---------------------|
| (+/-)x   | Unary sign operator |
| *        | Multiplication      |
| /        | Division            |
| +        | Addition            |
| -        | Subtraction         |
| %        | Modulo              |

## Compound assignment operators

| Operator | Description |            |
|----------|-------------|------------|
| +=       | a += b      | a = a + b  |
| -=       | a -= b      | a = a - b  |
| /=       | a /= b      | a = a / b  |
| \*=      | a \*= b     | a = a \* b |
| %=       | a %= b      | a = a % b  |

### Example

``` cpp
--8<-- "../ch_operators/operators1.cpp"
```

### Code output

    a = 68

## Increment and decrement operators (++/--)

* Increase / decrease variables by 1
* Can be used both prefix and postfix

  * ++a and a++
  * --a and a—

* Prefix version increases/decreases the value before returning result
* Postfix version increases/decreases the value after returning the result

### Example

``` cpp
--8<-- "../ch_operators/operators2.cpp"
```

### Code output

    b = 43
    c = 43

## Conditional operator ?

* Evaluates an expression, returning a value depending on the evaluation

  * condition ? result1 : result2
  * returns result1 if condition == true
  * returns result2 if condition == false

### Example

``` cpp
--8<-- "../ch_operators/operators3.cpp"
```

### Code output

    Enter a number : 45
    outValue = 21

    Enter a number : 55
    outValue = 42

## Expressions

``` cpp
-a + b + c1
```

Evaluates from left to right as:

``` cpp
((-a) + b) + c
```

The expression:

``` cpp
-a + b * c 
```

Evaluates as from left to right as:

``` cpp
    (-a) + (b * c)
```

## Mixed-mode expressions

* Numeric expressions with operands of differing datatypes
* Weaker of to datatypes will be coerced to the stronger one
* Result will be of the stronger type

``` cpp
    double a;
    int i;
    double b;

    b = a * i // i is coerced to double_types1
```

# C++ Strings

* Can use same strings as in C (char*)
* This course will use the std::string data type
* Very efficient and flexible string type
* Included in the C++ standard library
* Compatible with char* strings

  * can be passed as standard char* strings to legacy code (.c_str() method)

* Requires the #include <string> 

## Declaring and using C++ strings


### Example

``` cpp
--8<-- "../ch_strings/strings1.cpp"
```

### Code output

    a = 'hello'

.. note:: :cpp:`std::string` is the real variable type as it is part of the :cpp:`std` namespace 


String operations
-----------------

* Strings can be appended using the + operator
* Length of a string variable is returned by the .length() method
* Individual characters in the strings can be accessed by 

  * [index] operator
  * at(index) method

### Example

``` cpp
--8<-- "../ch_strings/strings2.cpp"
```

### Code output: ::

    s3 = 'hello, world'
    s3.length() = 12
    s3[7] = w
    s3.at(7) = w

## C++ String methods


* Methods for manipulating string content
* .append(string) can be used instead of the + operator to append strings to an existing string
* .replace(pos, n, string) – replaces n characters at position pos with the contents of string
* .insert(pos, string) – inserts string at position pos
* .substr(pos, n) – extracts n characters at position pos

### Example

``` cpp
--8<-- "../ch_strings/strings3.cpp"
```

### Code output

    s3 = hello, world. Strings in C++ are great!
    s3 = hello, world. Strings in C++ are nice! 
    s3 = hello, world. Strings in C++ are great and nice! 
    s4 = great 

## Searching C++ strings

* The find() method can be used to return position of substrings
* .find(string) – find first position of string
* .find(string, startpos) – find first position of string starting at startpos

### Example

``` cpp
--8<-- "../ch_strings/strings4.cpp"
```

### Code output

    The first 'o' is at position 12
    The next 'o' is at position 17

## Compatibility with C strings (char*)

* A std::string can be assigned a char* string

  * The opposite is not directly possible

* std::string:s can’t be directly used with C function requiring a char* argument.
* .c_str() method to the rescue

  * returns a const char* pointer wichi can be passed to functions and for assigning C style strings


### Example

``` cpp
--8<-- "../ch_strings/strings5.cpp"
```

.. note:: Allow for an extra position for the #0 character in the :cpp:`strncpy` call.  

.. note:: :cpp:`strncpy` is a overflow safe version of the C :cpp:`strcpy` function. 
 

### Code output

    cString = Hello, world!
    cString2 = Hello, world!

# Control structures

## Statements and compound statements

* C++ has 2 kind of statements

  * Normal statements separated by ;
  * Compound statements – normal statements grouped by { } (curly brackets)

* Compound statemtens are used in:

  * Function definitions
  * Conditional expressions
  * Iteration structures

## Iteration

* There are 3 iteration statements in C++

  * while – Condition before iteration statements
  * do – Condition after iteration statements
  * for – Compact version of the while-statement

* Iterations can be controlled by 

  * break-statement – exit a loop
  * continue – continue to next iteration
  * (goto-label statement)
  * return
  * exit() function

## while-statement

### Example

``` cpp
--8<-- "../ch_iterating/while_statement.cpp"
```

### Code output

    counter = 1
    counter = 2
    counter = 3
    counter = 4
    counter = 5
    counter = 7
    counter = 8
    counter = 9
    counter = 10

## do-statement

### Example

``` cpp
--8<-- "../ch_iterating/do_statement.cpp"
```

### Code output

    counter = 1
    counter = 2
    counter = 3
    counter = 4
    counter = 5
    counter = 7
    counter = 8
    counter = 9
    counter = 10

## for-statement

* Compact version of the do/while-statements
* for([start expression]; [conditional expression]; [step expression]

  * start expression is executed first before the first iteration
  * conditional expression is evaluated for each iteration
  * step expression is executed after the iteration statements for each iteration

* Creates more readable code compare to do/while-constructs


### Example

``` cpp
--8<-- "../ch_iterating/for_statement.cpp"
```

### Code output

    counter = 1
    counter = 2
    counter = 3
    counter = 4
    counter = 5
    counter = 7
    counter = 8
    counter = 9
    counter = 10

### Example

``` cpp
--8<-- "../ch_iterating/for_statement2.cpp"
```

## Code output: ::

    sum = 1656437623

## Controlling iteration
---------------------

### Example

``` cpp
--8<-- "../ch_iterating/for_statement.cpp"
```

### Code output

    counter = 1
    counter = 2
    counter = 3
    counter = 4
    counter = 5
    counter = 7
    counter = 8
    counter = 9

## Conditional statements

* There are 2 main conditional statements in C++
  
  * if-then-else – single or multiple conditions
  * switch – multiple path single condition

## Relational operators

| Operator | Meaning               | Python |
|----------|-----------------------|--------|
| <        | less than             | <      |
| <        | less than or equal    | <=     |
| ==       | equal                 | ==     |
| !=       | not equal             | !=     |
| >=       | greater than or equal | >=     |

## Logical operators

| Operator | Meaning | Python |
|----------|---------|--------|
| &&       | and     | and    |
| \|\|     | or      | or     |
| !        | not     | not    |

## if-statement

### Example

``` cpp
--8<-- "../ch_control_structures/if_statement1.cpp"
```

### Code output

    i = 1
    i = 2
    i = 3
    i = 4
    i = 5
    i == 5
    i = 6
    i = 7
    i = 8
    i = 9
    i = 10

``` cpp
--8<-- "../ch_control_structures/if_statement2.cpp"
```

### Code output

    i != 5
    i != 5
    i != 5
    i != 5
    i != 5
    i == 5
    i != 5
    i != 5
    i != 5
    i != 5
    i != 5

### Example

``` cpp
--8<-- "../ch_control_structures/if_statement3.cpp"
```

### Code output:

    i = 1: -
    i = 2: 2 <= i <= 3
    i = 3: 2 <= i <= 3
    i = 4: -
    i = 5: i == 5
    i = 6: -
    i = 7: -
    i = 8: -
    i = 9: -
    i = 10: -

## switch-statement

### Example

``` cpp
--8<-- "../ch_control_structures/switch_statement.cpp"
```

### Code output

    Color is green.
    Color is either BLUE, YELLOW or ORANGE.
    Color is either BLUE, YELLOW or ORANGE.
    Color is red.

