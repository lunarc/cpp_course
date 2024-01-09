# Input and output

On important aspect in programming is the ability to read and write from standard input/output and from to files in different ways. In C++ the main way of reading and writing data is using the streams classes in the **iostreams** library. Using streams data can be read and written using special operators to files. It is also possible to read and write to stream in memory. 

To use streams in C++ the include for the iostreams library has to be added as shown below:

```cpp
#include <iostreams>
```

The classes in the **iostreams** library are contained in the **std::** namespace, so if we want to use them directly they have to be prefixed with **std::**. For the examples in this chapter we will avoid this by adding the following statement in before use:

```cpp
using namespace std;
```

This is not recommended for larger projects, as it can bring in unnecessary namespaces in the code. This is escpecially important in header files.

## Reading and writing to the console

There are 3 built-in stream objects available for reading and writing to standard input - **cin**, standard output - **cout** and standard error - **cerr**. We have already used these objects in the previous sections without going into the details of how these work. 

Writing to a stream is accomplished using the **<<** operator followed by the variable, scalable or string that you want to write. Writing is done continously on a single line until a special object, **endl**, is passed to the stream. In the following example 3 variables are written to 2 lines of output:

```cpp
#include <iostream>

using namespace std;

int main()
{
    int a = 1;
    int b = 2;
    double c = 3.0;
    
    cout << a << " " << b;
    cout << " " << c << endl;
    cout << &c << endl;
}
```

Which gives the following output.

```
1 2 3
0x559fff6f0
```

The variables a, b and c are all written on the same line as the **endl** marker is passed after writing the **c** variable. You can also notice that passing a memory address to the stream will automatically format it as a hexadecimal memory address. 

Reading from a stream is done by using the **>>** operator followed by the variables that should be assigned from the input stream. How **cin** is used is shown in the example below:

```cpp
#include <iostream>

using namespace std;

int main()
{
    int a;
    int b;
    double c;
    
    cin >> a >> b >> c;
    
    cout << "a = " << a;
    cout << ", b = " << b;
    cout << ", c = " << c << endl;
}
```

In the example above the program will wait for 2 integers and a floating point number to be entered in the console before printing out the values in the **cout** statements.

## Formatting output using manipulators

To better control how output is written C++ provides a special manipulator operators that can be passed in the stream output to control the output of data written to the stream. To use this functionality we need to use the following include:

```cpp
#include <iomanip>
```

To control the width the output variables, the **setw(...)** manipulator can be used. This manipulator often needs to be called mutiple times as the width is usually reset if a **>>** or **<<** operators are used. It is also possible to control left and right alignment using the **left** and **right** manipulators. The character used to pad the output is set by the **setfill(...)** method and the precision of floating point values are set by the **setprecision(...)** manipulator. A complete example of using these manipulators is shown below:

```cpp
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
	double pi = 4 * std::atan(1);
    double x = 0.0;
    double dx = 0.1;
    
    cout << setw(15) << left << "X";
    cout << setw(10) << right << "f(x)" << endl;
    cout << setfill('-');
    cout << setw(25) << "" << endl;
    cout << setfill(' ');
    cout << setprecision(6) << fixed;
    //cout.unsetf(ios_base::fixed);
    
    while (x<=pi*0.25)
    {
        cout << setw(15) << left << x;
        cout << setw(10) << right << sin(x);
        cout << endl;
        x += dx;
    }
}
```

The code shown above will print a function table of the **sin(x)** function.

```
X                    f(x)
-------------------------
0.000000         0.000000
0.100000         0.099833
0.200000         0.198669
0.300000         0.295520
0.400000         0.389418
0.500000         0.479426
0.600000         0.564642
0.700000         0.644218
```

It is also possible to specifiy if a boolean value should be printed as 0 or 1 or with true and false.

```cpp
bool flag = true;

cout << "flag = " << flag << endl;
cout << boolalpha;
cout << "flag = " << flag << endl;
```

This prints:

```
flag = 1
flag = true
```

It is also possible to output values in different numerical bases using the **hex**, **dec** and **oct** manipulators. The **showbase** manipulator determines if output show the base in the output. The following code outputs the **n** integer in different bases.

```cpp
int n = 42;

cout << hex << "n = " << n << endl;
cout << hex << showbase << "n = " << n << endl;
cout << oct << "n = " << n << endl;
cout << dec << "n = " << n << endl;
```

This outputs the following:

```
n = 2a
n = 0x2a
n = 052
n = 42
```

The complete example is shown below:

```cpp
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    bool flag = true;
    
    cout << "flag = " << flag << endl;
    cout << boolalpha;
    cout << "flag = " << flag << endl;

    int n = 42;
    
    cout << hex << "n = " << n << endl;
    cout << hex << showbase << "n = " << n << endl;
    cout << oct << "n = " << n << endl;
    cout << dec << "n = " << n << endl;
}
```
 
There are a lot more manipulators available in the ***iomanip*** header. For more information please see:

[:fontawesome-solid-gears: iomanip att cppreference.com](https://en.cppreference.com/w/cpp/header/iomanip){ .md-button  .target="_blank"}

## Reading and writing to files

There are 2 main streams classes **ifstream** for reading from files and **ofstream** for writing to files. 