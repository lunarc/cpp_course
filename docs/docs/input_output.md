# Input and output

One important aspect of programming is the ability to read and write from standard input/output and from files in different ways. In C++ the main way of reading and writing data is using the stream classes in the C++ input/output library. Using streams, data can be read and written using special operators to files. It is also possible to read and write to stream in memory. 

The stream classes are defined in the **iostreams** header which is included with the following code:

```cpp
#include <iostreams>
```

The classes in **iostreams** are defined in the **std::** namespace, so if we want to use them directly they have to be prefixed with **std::**. For the examples in this chapter we will avoid this by adding the following statement in before use:

```cpp
using namespace std;
```

!!! note

    Adding this statement is not recommended for larger projects, as it can bring in unnecessary namespaces in the code. This is especially important in header files.

## Reading and writing to the console

There are 3 built-in stream objects available for reading and writing to standard input - **cin**, standard output - **cout** and standard error - **cerr**. We have already used these objects in the previous sections without going into the details of how these work. 

Writing to a stream is accomplished using the **<<** operator followed by the variable, scalable or string that you want to write. Writing is done continuously on a single line until a special manipulator, **endl**, is passed to the stream. In the following example 3 variables are written to 2 lines of output:

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

To read and write data to files we need to instantiate stream instances for each file operation. There are 3 main file stream classes in C++:

 * **ofstream** – output file stream
 * **ifstream** – input file stream
 * **fstream** – generic file stream

These classes are defined in the **fstream** standard header. Just like the **cout** and **cin** streams the file streams also use **<<** and **>>** operators for input and output. 

### Writing to a file (ofstream)

To open a file for writing we can use the **ofstream** class. The first step in writing to the file is to instantiate an output file stream.

```cpp
ofstream myfile;
```

Next, we open the file using the **open()**-method.

```cpp
myfile.open("myfile.txt");
```

As this is an output file stream we don't have to give any more arguments to the **open()**-method. The file is now open for writing and we can use the **<<**-operator for writing to the output stream.

```cpp
myfile << "Hello file!" << endl;
myfile << "Second line" << endl;
```

In the output to the file we can use the same manipulators as when we were outputting to the **cout** standard output stream. The last statements will write 2 rows to the file **myfile.txt**. 

The final step when reading and writing files is to tell the operating system that we will not work with the file anymore. This is done using the **.close()** method of the ofstream instance.

```cpp
myfile.close();
```

The complete example is shown below:

=== "Code"

    ``` cpp
    --8<-- "../ch_input_output/files1.cpp"
    ```

=== "Output (myfile.txt)"

    ```
    Hello file!
    Second line
    ```

### Appending to a file

The default behavior when writing to a file using the **ofstream** is to overwrite any existing file. If we want to append data to an existing file we can specify this using the second argument to the **.open()**-method, **ios::app**.

```cpp
myfile.open("myfile.txt", ios::app);
```

Everything we write to the stream will now be appended to the existing file.

```cpp
outfile << "Third line" << endl;
outfile.close();
```

This will add "Third line" as the third line of the **myfile.txt** file.

### Reading from a file (ifstream)

Reading from a file is done with the same steps as writing to a file. First, we instantiate an **ifstream** instance.

```cpp
ifstream myfile("myfile.txt");
```

When reading from a file it is always a good idea to make sure the file has been succesfully opened. This can be done using the **.is_open()** method of the stream instance.

```cpp
if (!myfile.is_open())
{
    cout << "The file couldn't be opened.\n";
    return;
}
```

A more generic way of checking if a file stream is ready for operations is to use the **.good()**-method. This method returns **true** if the file stream is ready for operations.

```cpp
if (!myfile.good())
    return
```

Reading from a file requires the file to have the data in a way that the file operators can interpret. Reading data types from a file requires them to be present in the same way as they were written to the file. Writing the variables **a**, **b** and **c** to disk as shown in the followng example 

```cpp
int a = 1;
int b = 2;
int c = 3;
myfile << a << b << c;
```

will produce the following output to the file:

```
123
```

This is probarbly not what you want and it will be impossible to read the data back again as integers. To write data to a file so that it is possible to read back we need to modify our example by adding space between the variables in the output.

```cpp
myfile << a << " " << b << " "<< c;
```

This produces the following output to the file:

```
1 2 3
```

Now it is also possible to read the data back from the file stream using the following statements:

```cpp
myfile >> a >> b >> c;
```

Notice that variables must be added in the same order as we wrote them to the file. We don't have to handle the extra spaces. Spaces between numbers in a file will automatically handled by the input operators.

### A larger example

To illustrate reading and writing values to a file we will create a program that will tabulate a function and write this to the file **inputfile.dat**. We start by creating an output stream for writing:

```cpp
double pi = 4 * std::atan(1);
double x = 0.0;
double y;
double dx = 0.1;

ofstream outfile;
outfile.open("inputfile.dat", ios::out);
```

Next, we use a while-loop to tabulate sin(x) from 0 to pi/4. For each row of the file we write the x value and the corresponding function value.

```cpp
while (x<=pi*0.25)
{
    outfile << x << " " << sin(x) << endl;
    x += dx;
}
outfile.close(); // Close file when we are done.
```

Notice that we add an extra space between **x** and **sin(x)**. When running this code the file **inputfile.dat** will contain the following:

```
0 0
0.1 0.0998334
0.2 0.198669
0.3 0.29552
0.4 0.389418
0.5 0.479426
0.6 0.564642
0.7 0.644218
```

To read the data back from **inputfile.dat** we instantiate a **ifstream** instance.

```cpp
ifstream infile;
infile.open("inputfile.dat");
```

Using a while-statement again we will read the file back. We use the **.good()** method to determine if we should exit the while-statement. As the input file contains values in the expected format we easily use the **>>**-operator for reading x and function values from the file.

```cpp
while (infile.good())
{
    infile >> x >> y;
    cout << "x = " << x << ", y = " << y << endl;
}
infile.close();
```

Output from the application will then be:

```
x = 0, y = 0
x = 0.1, y = 0.0998334
x = 0.2, y = 0.198669
x = 0.3, y = 0.29552
x = 0.4, y = 0.389418
x = 0.5, y = 0.479426
x = 0.6, y = 0.564642
x = 0.7, y = 0.644218
x = 0.7, y = 0.644218
```

The complete example can be found here:

=== "Code"

    ``` cpp
    --8<-- "../ch_input_output/files3.cpp"
    ```

=== "Output (myfile.txt)"

    ```
    x = 0, y = 0
    x = 0.1, y = 0.0998334
    x = 0.2, y = 0.198669
    x = 0.3, y = 0.29552
    x = 0.4, y = 0.389418
    x = 0.5, y = 0.479426
    x = 0.6, y = 0.564642
    x = 0.7, y = 0.644218
    x = 0.7, y = 0.644218
    ```

[:fontawesome-solid-gears: Try example](https://godbolt.org/z/xj4j5PvMY){ .md-button  .target="_blank"}

## Reading text files

Sometimes you want to read a text file and process the file yourself. To do this you can't use the standard stream operators. To read text from a file we use the standard library function **std::getline()** from the **sstream** header. This function takes a stream as input and a string containing the line that has been read from the file. In the following example we will read from a text file containing power consumtion data in CSV format. The first column contains the date for the sample and the second column contains the power consumtion value. First we open the file:

```cpp
string line;
ifstream infile;
infile.open("..\\..\\data\\AEP_hourly.csv");
```

We then do a while-loop over the file calling **std::getline(...)** to read the file line by line.

```cpp
while (infile.good())
{
    getline(infile, line);
    cout << line << endl;
}
infile.close();
```

Running the example will print out something similar to:

```
...
2006-05-23 12:00:00,15486.0
2006-05-23 13:00:00,15545.0
2006-05-23 14:00:00,15437.0
2006-05-23 15:00:00,15455.0
2006-05-23 16:00:00,15597.0
2006-05-23 17:00:00,15437.0
2006-05-23 18:00:00,15293.0
2006-05-23 19:00:00,15058.0
2006-05-23 20:00:00,14971.0
2006-05-23 21:00:00,15166.0
...
```


To process each line we need 
