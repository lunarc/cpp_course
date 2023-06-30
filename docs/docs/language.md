# Language

This chapter will go through the language elements of C++. To understand the language we will start with the fundamentals and transition to more modern features as we continue through this book. 

## Example of C++ code

An example of a simple C++ program is shown in the following example.

=== "Code"

    ``` c++
    --8<-- "../hello_world/hello.cpp"
    ```

=== "Output"

    ```
    0
    1
    2
    3
    4
    5
    6
    7
    8
    9
    Hello, C++
    ```

The example starts by including the **iostream** header, which provide means to output text in the terminal. The **using namespace std** statement just tells the compiler that the default namespace for the C++ standard library, **std**, will be used as the default, making it possible to omit the **std::**-prefix in front of all functions and objects. Namespaces will be covered later in the course.

**int main()** is the C++ main function, which will be called when the application starts. It is sometimes also called the application entry point.

**cout** is a special predefined object in C++ that can be used to output text and variables to the terminal. The **<<**-operator is used to send data to the **cout** object which will be sent to standard output for display in the terminal.

## Variables

Variables are references to data stored in memory and give you a way of referencing the data using a name instead of an address. Care should be given when assigning variable names so that they are self-explanatory.  

A naming convention that is often used in C++ is CamelCase. In this convention, names are formed by combining multiple words into single names, capitalizing the first letter of each word. Variables start with a lower case letter. Class names are all upper case. Examples can be:

``` cpp
class EquationSolver; // Classes are nouns. Start with upper case.
double length;        // variables start with lower case.
int totalNumber;      // variable with two words with camel case.
void myFunction();    // Functions and methods lower case CamelCase.
```

### Variable names

The C++ language also defines some rules regarding variable naming. Variables in C++ should consist of:

* Letters a-z, A-Z (not Å, Ä, Ö) 
* Numbers 0-9 
* Underscore _ 
* First character must be a letter or an underscore.
* Lower case letters are not equivalent with upper case letters. Case sensitive language.

The following variable names are correct:

``` cpp
int i, j;
double x, y;
double z0;
bool correct_answer;
```

The following variable names are not correct:

``` cpp
int 0i;
double å0;
```

### Declaring variables

C++ is a strongly type language and all variables needs to be declared with a type. A variable is declared by specifying the type followed by the variable name as shown in the following example:

``` cpp 
int a;
double c;
float x;
```


In this example, an integer variable a, a double variable c and a float variable x is declared. 

!!! note

    Values of declared undefined until they have been initialized.  

### Variable initialisation

Before a variable is used it should be initialized, that is given a value. There are 2 ways of initialising a variable in C++. As C++ inherits a lot from C, variables can be initialised just like in C by assigning a value when the variable is declared using the equal (=) operator. In the following example we initialise variables at the same time as they are created using C style initialisation.

``` cpp 
int i = 0;
float x = 0.0;
```

Another way of initializing variables is using constructor-based initialization, which is specific to the C++ language. In this method, the variable is initialized by specifying the initial value in parenthesis:

``` cpp
int i(0);
float x(0.0);
```

The final way of initializing values is using uniform initialization. This is also specific to the C++ language and uses curly brackets to assign initial values to variables. 

``` cpp
int i{0};
float x{0.0};
```

All these ways of initializing variables are equivalent. You will see some different ways of initializing variables in this book. Which type of initialization is chosen depends on the situation. In certain situations one method can be more efficient than others. In other cases the code can be more readable using a certain example.

### Variable types

In C++ there are 7 fundamental datatypes that can be used. 

 * Character types - **char**, **char16_t**, **char32_t**, **wchar_t**
 * Signed integer types - **short**, **int**, **long**, **long long**
 * Unsigned integer type - **unsigned short**, **unsigned int**, **unsigned long**, **unsigned long long**.
 * Floating point types - **float**, **double**, **long double**
 * Boolean type - **bool**
 * void type - **void**
 * nullptr - **decltype(nullptr)**

Sizes of variables types depend on platform and compiler. C++ only specifies sizes relative to other types with at least number of bits.

In the following chapters we will cover these datatypes in more details.

### Integer types

Integer datatypes come in two flavors signed and unsigned. The basic signed integer type is **int**, which corresponds to **signed int**. The corresponding unsigned variable type is **unsigned int**. Unsigned variables always require the prefix **unsigned**. The available datatypes with increasing size:

 * **signed char** / **unsigned char**
 * **short int** / **unsigned short int**
 * **int** / **unsigned int** 
 * **long int** / **unsigned long**

!!! note

    Don't use unsigned to prevent negative values. This can lead to conversion errors later on.

Unsigned integers can be used to represent bit patterns.

The following code shows how different integer types are delcared and assigned. Please note what happens if you assign a negative value to an unsigned integer.

=== "Code"

    ``` cpp
    --8<-- "../ch_variables/int_types1.cpp"
    ```

=== "Output"

    ```
    a = -1
    b = 4294967295
    c = -1
    d = 18446744073709551615
    ```

The size of an integer depends on the compiler and platform. C++ just provides relative guarantees between the different datatypes. The actual size of a datatype can be queried using the **std::sizeof()** function. This function returns the size in multiples of sizeof(char)=1. The relationship between the integer datatypes are:

> 1 = sizeof(char) ≤ sizeof(short) ≤ sizeof(int) ≤ sizeof(long)

In the code below the **std::sizeof()** to query the exact size of the datatypes on the current platform.

=== "Code"

    ``` cpp
    --8<-- "../ch_variables/int_types2.cpp"
    ```
=== "Output"

    ```
    a = -1, sizeof(a) = 4
    b = 4294967295, sizeof(b) = 4
    c = -1, sizeof(c) = 8
    d = 18446744073709551615, sizeof(d) = 8
    ```
        
### Character types

Character types contain values that correspond to the values from a character set. Character sets are guaranteed to contain numeric characters, 26 letters of the english alphabet and common delimiters. The smallest character type is **char**, which should be at least 8 bits (0..255). This can vary from different systems. The default type, **char**, is unsigned. There is also a signed version (-128..127). To support additional character sets there are alos additional character types:

 * **char16_t** - at least 16 bits
 * **char32_t** - at least 32 bits
 * **wchar_t** - supporting the largest character set
 
It is possible to convert from **char** to integer using the **int()** function.

=== "Code"

    ``` cpp
    --8<-- "../ch_variables/char_types1.cpp"
    ```

=== "Output"

    ```
    c = a int(c) = 97 sizeof(c) = 1
    uc = ª int(uc) = 170 sizeof(c) = 1
    sc = ‚ int(sc) = -126 sizeof(c) = 1
    c16 = b int(c16) = 98 sizeof(c16) = 2
    c32 = c int(c32) = 99 sizeof(c32) = 2
    w32 = d int(w32) = 100 sizeof(w32) = 2
    ```

!!! note 

    **cout** does not support unicode characters or **char16_t** or **char32_t**, which requires us to use the **wcout** operator instead and make a conversion to **wchar_t** instead.

### Floating point types

Floating point datatypes are the essential buildingblocks of compuational codes. C++ support 3 floating point types:

 * **float** - single precision
 * **double** - double precision. Higher precision than float.
 * **long double** - extended precision. Higher precision that double.

If your computational relies on precision use **double**. The actual size of the types is compiler dependent. Usually the **long double** can be inefficient as this datatype is often not implemented in the processor architecture and the compiler will have to generate special CPU code for working with this datatype.

=== "Code"

    ``` cpp
    --8<-- "../ch_variables/double_types1.cpp"
    ```

=== "Output"

    ```
    f = 3.14159274101257
    d = 3.14159265358979
    ld = 3.14159265358979
    ```

### Floating point literals

When assigning values to variables in C++ in can sometimes be required/benficial to specify the datatype of the scalar value specified in the source code (floating point literal). This can be done using suffixes on the value in the code. If no suffix is given on a value the datatype is assumed to be **double**. The following example illustrates the use of suffixes when specifying floating point literals: 

``` cpp
float a = 1.0f;       // 1.0f is float
double b = 1.0;       // 1.0 is assumed to be double
long double c = 1.0l; // 1.0l is long double
```

It is also possible to use literals with suffixes for literals in scientific notation:

``` cpp
float d = 1e300f;          // float
double e = 1e-300;         // double
long double f = 42.0e-40l; // long double
```

### Numerical limits

To query the capabilites of datatypes, C++ provides functions for this in the **<limits>** include file. Using the functions in this module it is possible to query max and min ranges for any standard data types. To query the largest value of a datatype use the **std::numeric_limits<[datatype]>::max()** function. In the same way query the lowest value using the **std::numeric_limits<[datatype]>::min()** function. It is also possible to check if a datatype is signed using the **std::numeric_limits<[datatype]>::is_signed** flag. The follwing example show how the functions are used:


=== "Code"

    ``` cpp
    --8<-- "../ch_variables/numerical_limits.cpp"
    ```

=== "Output"

    ```
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
    ```

### Enumeration types

* Defines different kinds of enumerations
* Can be used as an integer type
* By default enumeration constants are given integer values in the order they are defined
* Specific values can be given to the enumeration constants.
* An enumeration can be a distinct data type.
* Converted to integers in expressions

=== "Code"

    ``` cpp
    --8<-- "../ch_variables/enum_types.cpp"
    ```

=== "Output"

    ```
    RED = 0
    GREEN = 1
    BLUE = 2
    YELLOW = 3
    selectedFlavor = 2
    currentStatus = 15
    ```

### Class enumerations


### Arrays

* “List of elements with a specific data type”
* Indexed from 0 … size - 1
* Brackets [ ] is used for accessing individual elements
* Declaration

  * [data type] name[size] [ = { list of values} ]

* Contigous multidimensional array not supported with indices. Tricks and OO can solve this 

=== "Code"

    ``` cpp
    --8<-- "../ch_variables/array_types1.cpp"
    ```

=== "Output"

    ```
    1, 2
    1, 2, 3, 42
    ```
    
### Pointers

* Declared with the * operator
* Can be typed and untyped (void*)
* Declaration

  * [data type]* name

* Pointer variable contains a memory address
* * operator is also used to dereference pointer and retrieve value at memory location
* & operator can be used to return a memory address for a non-pointer variable. 

=== "Code"

    ``` cpp
    --8<-- "../ch_variables/pointers1.cpp"
    ```

=== "Output"

    ```
    a = 42
    b = 0x7fff5fbff6bc
    &a = 0x7fff5fbff6bc
    *b = 42
    ```

<img src="../images/pointers1.svg" width="50%">

<img src="../images/pointers1-2.svg" width="50%">

\*b is the value stored at memory location b 

### Array pointer duality

* Array and pointers are very related in C/C++
* Pointer types can be accessed using array notation
* Arrays can be accessed like pointers
* Increases flexibility in algorithm design
* Increases risk of errors as well

=== "Code"

    ``` cpp
    --8<-- "../ch_variables/pointers2.cpp"
    ```

=== "Output"

    ```
    a = 0x7fff5fbff6a0
    b = 0x7fff5fbff6a0
    a[0] = 0
    b[0] = 0
    *b = 0
    *a = 0
    c = 0x7fff5fbff6a8
    *c = 2
    ```


<img src="../images/pointers1-3.svg" width="50%">


### Constants

* A way of defining data that is not changed during program execution
* Use instead of numeric constants in the code

  * Easier to update code in a later stage

* Prevents accidental modification of variables
* Gives hints to the compiler on optmisations

  * Precomputing expressions at compile time
  * Reduce memory usage

=== "Code"

    ``` cpp
    --8<-- "../ch_variables/const_types.cpp"
    ```
    
### References

* Alternative names for a variables
* Mainly used in function arguments
* [data type]& name

  * Defines a reference to another variable of the same data type

=== "Code"

    ``` cpp
    --8<-- "../ch_variables/reference_type.cpp"
    ```

=== "Output"

    ```
    a = 42
    b = 42
    &a = 0x7fff5fbff6bc
    &b = 0x7fff5fbff6bc
    ```

* b points to the same memory location as a

* b can be used as a normal variable after it has been initialised 

### Structured data types

* Data type consisting of a mix of other data types
* Compare entries in a database

  * first name
  * last name
  * street
  * ...
  
* Declared using the struct keyword
* Members are accessed with . (dot) or -> operators

=== "Code"

    ``` cpp
    --8<-- "../ch_variables/structured_type.cpp"
    ```

=== "Output"

    ```
    c1.x = 0, c1.y = 0
    c2.x = 1, c2.y = 1
    sizeof(c1) = 16
    ```

## Expressions and operators

### Arithmetic operators

| Operator | Description         |
|----------|---------------------|
| (+/-)x   | Unary sign operator |
| *        | Multiplication      |
| /        | Division            |
| +        | Addition            |
| -        | Subtraction         |
| %        | Modulo              |

### Compound assignment operators

| Operator | Description |            |
|----------|-------------|------------|
| +=       | a += b      | a = a + b  |
| -=       | a -= b      | a = a - b  |
| /=       | a /= b      | a = a / b  |
| \*=      | a \*= b     | a = a \* b |
| %=       | a %= b      | a = a % b  |

=== "Code"

    ``` cpp
    --8<-- "../ch_operators/operators1.cpp"
    ```

=== "Output"

    ```
    a = 68
    ```

### Increment and decrement operators (++/--)

* Increase / decrease variables by 1
* Can be used both prefix and postfix

  * ++a and a++
  * --a and a—

* Prefix version increases/decreases the value before returning result
* Postfix version increases/decreases the value after returning the result

=== "Code"

    ``` cpp
    --8<-- "../ch_operators/operators2.cpp"
    ```

=== "Output"

    ```
    b = 43
    c = 43
    ```

### Conditional operator ?

* Evaluates an expression, returning a value depending on the evaluation

  * condition ? result1 : result2
  * returns result1 if condition == true
  * returns result2 if condition == false

=== "Example"

    ``` cpp
    --8<-- "../ch_operators/operators3.cpp"
    ```

=== "Output"

    ```
    Enter a number : 45
    outValue = 21

    Enter a number : 55
    outValue = 42
    ```

### Expressions

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

### Mixed-mode expressions

* Numeric expressions with operands of differing datatypes
* Weaker of to datatypes will be coerced to the stronger one
* Result will be of the stronger type

``` cpp
double a;
int i;
double b;

b = a * i // i is coerced to double_types1
```

## Strings

* Can use same strings as in C (char*)
* This course will use the std::string data type
* Very efficient and flexible string type
* Included in the C++ standard library
* Compatible with char* strings

  * can be passed as standard char* strings to legacy code (.c_str() method)

* Requires the #include <string> 

### Declaring and using C++ strings

=== "Example"

    ``` cpp
    --8<-- "../ch_strings/strings1.cpp"
    ```
=== "Output"

    ```
    a = 'hello'
    ```

!!! Note

    `std::string` is the real variable type as it is part of the :`std` namespace. 


### String operations

* Strings can be appended using the + operator
* Length of a string variable is returned by the .length() method
* Individual characters in the strings can be accessed by 

  * [index] operator
  * at(index) method

=== "Example"

    ``` cpp
    --8<-- "../ch_strings/strings2.cpp"
    ```

=== "Output"

    ```
    s3 = 'hello, world'
    s3.length() = 12
    s3[7] = w
    s3.at(7) = w
    ```

### C++ String methods

* Methods for manipulating string content
* .append(string) can be used instead of the + operator to append strings to an existing string
* .replace(pos, n, string) – replaces n characters at position pos with the contents of string
* .insert(pos, string) – inserts string at position pos
* .substr(pos, n) – extracts n characters at position pos

=== "Example"

    ``` cpp
    --8<-- "../ch_strings/strings3.cpp"
    ```

=== "Output"

    ```
    s3 = hello, world. Strings in C++ are great!
    s3 = hello, world. Strings in C++ are nice! 
    s3 = hello, world. Strings in C++ are great and nice! 
    s4 = great 
    ```

### Searching C++ strings

* The find() method can be used to return position of substrings
* .find(string) – find first position of string
* .find(string, startpos) – find first position of string starting at startpos

=== "Example"

    ``` cpp
    --8<-- "../ch_strings/strings4.cpp"
    ```

=== "Output"

    ```
    The first 'o' is at position 12
    The next 'o' is at position 17
    ```

### Compatibility with C strings (char*)

* A std::string can be assigned a char* string

  * The opposite is not directly possible

* std::string:s can’t be directly used with C function requiring a char* argument.
* .c_str() method to the rescue

  * returns a const char* pointer wichi can be passed to functions and for assigning C style strings


=== "Example"

    ``` cpp
    --8<-- "../ch_strings/strings5.cpp"
    ```

=== "Output"

    ```
    cString = Hello, world!
    cString2 = Hello, world!
    ```


!!! note

    Allow for an extra position for the #0 character in the `strncpy` call.  

!!! note

    `strncpy` is a overflow safe version of the C `strcpy` function. 
 


## Control structures

### Statements and compound statements

* C++ has 2 kind of statements

  * Normal statements separated by ;
  * Compound statements – normal statements grouped by { } (curly brackets)

* Compound statemtens are used in:

  * Function definitions
  * Conditional expressions
  * Iteration structures

### Iteration

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

### while-statement

=== "Example"

    ``` cpp
    --8<-- "../ch_iterating/while_statement.cpp"
    ```

=== "Output"

    ```
    counter = 1
    counter = 2
    counter = 3
    counter = 4
    counter = 5
    counter = 7
    counter = 8
    counter = 9
    counter = 10
    ```

### do-statement

=== "Example"

    ``` cpp
    --8<-- "../ch_iterating/do_statement.cpp"
    ```

=== "Output"

    ```
    counter = 1
    counter = 2
    counter = 3
    counter = 4
    counter = 5
    counter = 7
    counter = 8
    counter = 9
    counter = 10
    ```

### for-statement

* Compact version of the do/while-statements
* for([start expression]; [conditional expression]; [step expression]

  * start expression is executed first before the first iteration
  * conditional expression is evaluated for each iteration
  * step expression is executed after the iteration statements for each iteration

* Creates more readable code compare to do/while-constructs


=== "Example"

    ``` cpp
    --8<-- "../ch_iterating/for_statement.cpp"
    ```

=== "Output"

    ```
    counter = 1
    counter = 2
    counter = 3
    counter = 4
    counter = 5
    counter = 7
    counter = 8
    counter = 9
    counter = 10
    ```

=== "Example"

    ``` cpp
    --8<-- "../ch_iterating/for_statement2.cpp"
    ```

=== "Output"

    ```
    sum = 1656437623
    ```

### Controlling iteration

=== "Example"

    ``` cpp
    --8<-- "../ch_iterating/for_statement.cpp"
    ```

=== "Output"

    ```
    counter = 1
    counter = 2
    counter = 3
    counter = 4
    counter = 5
    counter = 7
    counter = 8
    counter = 9
    ```

### Conditional statements

* There are 2 main conditional statements in C++
  
  * if-then-else – single or multiple conditions
  * switch – multiple path single condition

### Relational operators

| Operator | Meaning               | Python |
|----------|-----------------------|--------|
| <        | less than             | <      |
| <        | less than or equal    | <=     |
| ==       | equal                 | ==     |
| !=       | not equal             | !=     |
| >=       | greater than or equal | >=     |

### Logical operators

| Operator | Meaning | Python |
|----------|---------|--------|
| &&       | and     | and    |
| \|\|     | or      | or     |
| !        | not     | not    |

### if-statement

=== "Example"

    ``` cpp
    --8<-- "../ch_control_structures/if_statement1.cpp"
    ```

=== "Output"

    ```
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
    ```

=== "Example"

    ``` cpp
    --8<-- "../ch_control_structures/if_statement2.cpp"
    ```

=== "Output"

    ```
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
    ```

=== "Example"

    ``` cpp
    --8<-- "../ch_control_structures/if_statement3.cpp"
    ```

=== "Output"

    ```
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
    ```

### switch-statement

=== "Example"

    ``` cpp
    --8<-- "../ch_control_structures/switch_statement.cpp"
    ```

=== "Output"

    ```
    Color is green.
    Color is either BLUE, YELLOW or ORANGE.
    Color is either BLUE, YELLOW or ORANGE.
    Color is red.
    ```

## Functions

* Use functions to modularise a program
* Format:
    - return type name(parameters) { statements } 
* Return type can be specified as void if nothing is to be returned
* Call a function by giving the name and parameters
    - variable = myfunc(parameters)
    - myfunc2(parameters)

=== "Example"

    ``` cpp
    --8<-- "../ch_functions/functions1.cpp"
    ```

=== "Output"

    ```
    Hello, from function!
    ```

### Function parameters

* By default a parameter is passed by value
    - void myfunc(double a)
    - a will be a copy of the variable passed in the call

=== "Example"

    ``` cpp
    --8<-- "../ch_functions/functions2.cpp"
    ```

=== "Output"

    ```
    The value of a = 42
    ```

Pass by value:

=== "Example"

    ``` cpp
    --8<-- "../ch_functions/functions3.cpp"
    ```

=== "Output"

    ```
    The value of a = 42
    &a = 0x7fff5fbff69c
    &a = 0x7fff5fbff6bc
    ```

### Scalar parameters by reference

* Pass pointer to variable
    - void myfunc(double* a)
* Send address of variable in call
    - myfunc(&a)
* In function variable must be derefenced using the * operator
    - *a = 42

=== "Example"

    ``` cpp
    --8<-- "../ch_functions/functions4.cpp"
    ```

=== "Output"

    ```
    The value of a = 0x7fff5fbff6bc
    *a = 42
    ```

* Better solution using the reference operator &
* Pass by reference
    - void myfunc(double& a)
* Call function with actual variable
    - myfunc(a)
* No need for dereferencing a refers to passed variable
    - a = 42

=== "Example"

    ``` cpp
    --8<-- "../ch_functions/functions5.cpp"
    ```

=== "Output"

    ```
    Before function call: a = 42
    After function call : a = 43
    ```

### Passing arrays

* Arrays can be passed by pointer operator * or [] index operator
    - Equivalent 
* By pointer operator
    - void myfunc(int* array)
* By bracket operator
    - void myfunc(int array[])

=== "Example"

    ``` cpp
    --8<-- "../ch_functions/functions7.cpp"
    ```

=== "Output"

    ```
    1, 2, 3, 4, 
    ```

Using bracket operators:

=== "Example"

    ``` cpp
    --8<-- "../ch_functions/functions8.cpp"
    ```

=== "Output"

    ```
    1, 2, 3, 4, 
    ```


## Memory allocation

### Memory allocation in C++

### Dynamic memory allocation

### Two-dimensional arrays C++ Style

### Two-dimensional array Fortran Style

### Functions for 2D arrays

### Dynamic arrays of struct


