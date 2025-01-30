Input and output
================

.. image:: images/input_output.png
   :width: 100.0%

One important aspect of programming is the ability to read and write
from standard input/output and from files in different ways. In C++ the
main way of reading and writing data is using the stream classes in the
C++ input/output library. Using streams, data can be read and written
using special operators to files. It is also possible to read and write
to stream in memory.

The stream classes are defined in the **iostreams** header which is
included with the following code:

.. code:: cpp

   #include <iostreams>

The classes in **iostreams** are defined in the **std::** namespace, so
if we want to use them directly they have to be prefixed with **std::**.
For the examples in this chapter we will avoid this by adding the
following statement in before use:

.. code:: cpp

   using namespace std;


.. note:: 
   Adding this statement is not recommended for larger projects, as it can bring in unnecessary namespaces in the code. This is especially important in header files.

Reading and writing to the console
----------------------------------

There are 3 built-in stream objects available for reading and writing to
standard input - **cin**, standard output - **cout** and standard error
- **cerr**. We have already used these objects in the previous sections
without going into the details of how these work.

Writing to a stream is accomplished using the **<<** operator followed
by the variable, scalable or string that you want to write. Writing is
done continuously on a single line until a special manipulator,
**endl**, is passed to the stream. In the following example 3 variables
are written to 2 lines of output:

.. code:: cpp

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

Which gives the following output.

::

   1 2 3
   0x559fff6f0

The variables a, b and c are all written on the same line as the
**endl** marker is passed after writing the **c** variable. You can also
notice that passing a memory address to the stream will automatically
format it as a hexadecimal memory address.

Reading from a stream is done by using the **>>** operator followed by
the variables that should be assigned from the input stream. How **cin**
is used is shown in the example below:

.. code:: cpp

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

In the example above the program will wait for 2 integers and a floating
point number to be entered in the console before printing out the values
in the **cout** statements.

Formatting output using manipulators
------------------------------------

To better control how output is written C++ provides a special
manipulator operators that can be passed in the stream output to control
the output of data written to the stream. To use this functionality we
need to use the following include:

.. code:: cpp

   #include <iomanip>

To control the width the output variables, the **setw(…)** manipulator
can be used. This manipulator often needs to be called mutiple times as
the width is usually reset if a **>>** or **<<** operators are used. It
is also possible to control left and right alignment using the **left**
and **right** manipulators. The character used to pad the output is set
by the **setfill(…)** method and the precision of floating point values
are set by the **setprecision(…)** manipulator. A complete example of
using these manipulators is shown below:

.. code:: cpp

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

The code shown above will print a function table of the **sin(x)**
function.

::

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

It is also possible to specifiy if a boolean value should be printed as
0 or 1 or with true and false.

.. code:: cpp

   bool flag = true;

   cout << "flag = " << flag << endl;
   cout << boolalpha;
   cout << "flag = " << flag << endl;

This prints:

::

   flag = 1
   flag = true

It is also possible to output values in different numerical bases using
the **hex**, **dec** and **oct** manipulators. The **showbase**
manipulator determines if output show the base in the output. The
following code outputs the **n** integer in different bases.

.. code:: cpp

   int n = 42;

   cout << hex << "n = " << n << endl;
   cout << hex << showbase << "n = " << n << endl;
   cout << oct << "n = " << n << endl;
   cout << dec << "n = " << n << endl;

This outputs the following:

::

   n = 2a
   n = 0x2a
   n = 052
   n = 42

The complete example is shown below:

.. code:: cpp

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

There are a lot more manipulators available in the **iomanip** header.
For more information please see:

.. button-link:: https://en.cppreference.com/w/cpp/header/iomanip
    :color: primary
    :outline:

    cppreference.com


Reading and writing to files (streams)
--------------------------------------

To read and write data to files we need to instantiate stream instances
for each file operation. There are 3 main file stream classes in C++:

- **ofstream** – output file stream
- **ifstream** – input file stream
- **fstream** – generic file stream

These classes are defined in the **fstream** standard header. Just like
the **cout** and **cin** streams the file streams also use **<<** and
**>>** operators for input and output.

Writing to a file (ofstream)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To open a file for writing we can use the **ofstream** class. The first
step in writing to the file is to instantiate an output file stream.

.. code:: cpp

   ofstream myfile;

Next, we open the file using the **open()**-method.

.. code:: cpp

   myfile.open("myfile.txt");

As this is an output file stream we don’t have to give any more
arguments to the **open()**-method. The file is now open for writing and
we can use the **<<**-operator for writing to the output stream.

.. code:: cpp

   myfile << "Hello file!" << endl;
   myfile << "Second line" << endl;

In the output to the file we can use the same manipulators as when we
were outputting to the **cout** standard output stream. The last
statements will write 2 rows to the file **myfile.txt**.

The final step when reading and writing files is to tell the operating
system that we will not work with the file anymore. This is done using
the **.close()** method of the ofstream instance.

.. code:: cpp

   myfile.close();

The complete example is shown below:

.. tabs::

   .. tab:: Code

         .. literalinclude:: ../../ch_input_output/files1.cpp

   .. tab:: Output (myfile.txt)

      .. code-block::

         Hello file!
         Second line

Appending to a file
~~~~~~~~~~~~~~~~~~~

The default behavior when writing to a file using the **ofstream** is to
overwrite any existing file. If we want to append data to an existing
file we can specify this using the second argument to the
**.open()**-method, **ios::app**.

.. code:: cpp

   myfile.open("myfile.txt", ios::app);

Everything we write to the stream will now be appended to the existing
file.

.. code:: cpp

   outfile << "Third line" << endl;
   outfile.close();

This will add “Third line” as the third line of the **myfile.txt** file.

Reading from a file (ifstream)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Reading from a file is done with the same steps as writing to a file.
First, we instantiate an **ifstream** instance.

.. code:: cpp

   ifstream myfile("myfile.txt");

When reading from a file it is always a good idea to make sure the file
has been succesfully opened. This can be done using the **.is_open()**
method of the stream instance.

.. code:: cpp

   if (!myfile.is_open())
   {
       cout << "The file couldn't be opened.\n";
       return;
   }

A more generic way of checking if a file stream is ready for operations
is to use the **.good()**-method. This method returns **true** if the
file stream is ready for operations.

.. code:: cpp

   if (!myfile.good())
       return

Reading from a file requires the file to have the data in a way that the
file operators can interpret. Reading data types from a file requires
them to be present in the same way as they were written to the file.
Writing the variables **a**, **b** and **c** to disk as shown in the
followng example

.. code:: cpp

   int a = 1;
   int b = 2;
   int c = 3;
   myfile << a << b << c;

will produce the following output to the file:

::

   123

This is probarbly not what you want and it will be impossible to read
the data back again as integers. To write data to a file so that it is
possible to read back we need to modify our example by adding space
between the variables in the output.

.. code:: cpp

   myfile << a << " " << b << " "<< c;

This produces the following output to the file:

::

   1 2 3

Now it is also possible to read the data back from the file stream using
the following statements:

.. code:: cpp

   myfile >> a >> b >> c;

Notice that variables must be added in the same order as we wrote them
to the file. We don’t have to handle the extra spaces. Spaces between
numbers in a file will automatically handled by the input operators.

A larger example
~~~~~~~~~~~~~~~~

To illustrate reading and writing values to a file we will create a
program that will tabulate a function and write this to the file
**inputfile.dat**. We start by creating an output stream for writing:

.. code:: cpp

   double pi = 4 * std::atan(1);
   double x = 0.0;
   double y;
   double dx = 0.1;

   ofstream outfile;
   outfile.open("inputfile.dat", ios::out);

Next, we use a while-loop to tabulate sin(x) from 0 to pi/4. For each
row of the file we write the x value and the corresponding function
value.

.. code:: cpp

   while (x<=pi*0.25)
   {
       outfile << x << " " << sin(x) << endl;
       x += dx;
   }
   outfile.close(); // Close file when we are done.

Notice that we add an extra space between **x** and **sin(x)**. When
running this code the file **inputfile.dat** will contain the following:

::

   0 0
   0.1 0.0998334
   0.2 0.198669
   0.3 0.29552
   0.4 0.389418
   0.5 0.479426
   0.6 0.564642
   0.7 0.644218

To read the data back from **inputfile.dat** we instantiate a
**ifstream** instance.

.. code:: cpp

   ifstream infile;
   infile.open("inputfile.dat");

Using a while-statement again we will read the file back. We use the
**.good()** method to determine if we should exit the while-statement.
As the input file contains values in the expected format we easily use
the **>>**-operator for reading x and function values from the file.

.. code:: cpp

   while (infile.good())
   {
       infile >> x >> y;
       cout << "x = " << x << ", y = " << y << endl;
   }
   infile.close();

Output from the application will then be:

::

   x = 0, y = 0
   x = 0.1, y = 0.0998334
   x = 0.2, y = 0.198669
   x = 0.3, y = 0.29552
   x = 0.4, y = 0.389418
   x = 0.5, y = 0.479426
   x = 0.6, y = 0.564642
   x = 0.7, y = 0.644218
   x = 0.7, y = 0.644218

The complete example can be found here:

.. tabs::

   .. tab:: Code

      .. literalinclude:: ../../ch_input_output/files3.cpp

   .. tab:: Output (myfile.txt)

      .. code-block::

         x = 0, y = 0
         x = 0.1, y = 0.0998334
         x = 0.2, y = 0.198669
         x = 0.3, y = 0.29552
         x = 0.4, y = 0.389418
         x = 0.5, y = 0.479426
         x = 0.6, y = 0.564642
         x = 0.7, y = 0.644218
         x = 0.7, y = 0.644218

.. button-link:: https://godbolt.org/z/xj4j5PvMY
    :color: primary
    :outline:

    Try example


Reading text files
------------------

Sometimes you want to read a text file and process the file yourself. To
do this you can’t use the standard stream operators. To read text from a
file we use the standard library function **std::getline()** from the
**sstream** header. This function takes a stream as input and a string
containing the line that has been read from the file. In the following
example we will read from a text file containing power consumtion data
in CSV format. The first column contains the date for the sample and the
second column contains the power consumtion value. First we open the
file:

.. code:: cpp

   string line;
   ifstream infile;
   infile.open("..\\..\\data\\AEP_hourly.csv");

   if (!infile.is_open())
   {
       cout << "Error opening file" << endl;
       return 1;
   }

We then do a while-loop over the file calling **std::getline(…)** to
read the file line by line.

.. code:: cpp

   while (infile.good())
   {
       getline(infile, line);
       cout << line << endl;
   }
   infile.close();

Running the example will print out something similar to:

::

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

Splitting lines
~~~~~~~~~~~~~~~

To separate the date from the value we need to do some basic string
manipulation. First we need to find the position of the comma in the
line. We can do this with the **std::find(…)** method. This function
will return a string iterator at the position of the comma or end
**end()** iterator. We can then use the **.substr()** method of the
string to extract the date and value fields. The code then becomes:

.. code:: cpp

   while (infile.good())
   {
       getline(infile, line);

       auto pos = std::find(line.begin(), line.end(), ',');

       if (pos != line.end())
       {
           string date = line.substr(0, pos - line.begin());
           string value = line.substr(pos - line.begin() + 1);

           std::cout << "date:  " << date << " value: " << value << "\n";
       }
   }

Running this code produces the following output:

::

   date:  2018-01-01 12:00:00 value: 19453.0
   date:  2018-01-01 13:00:00 value: 19049.0
   date:  2018-01-01 14:00:00 value: 18737.0
   date:  2018-01-01 15:00:00 value: 18619.0
   date:  2018-01-01 16:00:00 value: 18691.0
   date:  2018-01-01 17:00:00 value: 19109.0
   date:  2018-01-01 18:00:00 value: 20279.0
   date:  2018-01-01 19:00:00 value: 20925.0
   date:  2018-01-01 20:00:00 value: 21089.0
   date:  2018-01-01 21:00:00 value: 20999.0
   date:  2018-01-01 22:00:00 value: 20820.0
   date:  2018-01-01 23:00:00 value: 20415.0
   date:  2018-01-02 00:00:00 value: 19993.0

Converting from string to float
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If we want to convert the value field to a floating point type we can
use the **std::stod(…)** or **std::stof(…)** functions. They throw an
**std::invalid_argument** exception if the value can’t be converted. The
conversion can be handled using the following code:

.. code:: cpp

   double dval = 0.0;

   try
   {
       dval = std::stod(strValue);
   }
   catch (const std::exception& e)
   {
       std::cerr << e.what() << '\n';
   }

   std::cout << "date:  " << date << " value: " << dval << "\n";

Reading binary files
--------------------

In the previous chapters we have seen how we can read and write data to
text files. In many cases you will need to read and write data in binary
format. Reading and writing to binary files are similar to the previous
approach except that we add the **ios::binary** flag in the
open-statement. and instead of using the **<<** and **>>** operators we
use the stream methods **.read(…)** and **.write(…)** methods for read
and write. I binary file can also consist of multiple parts with
different data (records). To be able to read data at different parts of
the file we use an invisble cursor that we can place at the location we
want to read. This cursor can be set using the **.seekg(…)** method of
the stream.

Writing data to a binary file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In this example we are going to write a number of particles with
position and mass to disk as a binary file. First we create a structure
to hold the particle information.

.. code:: cpp

   struct Particle {
       double x;
       double y;
       double mass;
   };

For this example we are going to write random data to our particles, so
we initialise the random number generator.

.. code:: cpp

   srand((unsigned)time(0));

Next, we open a stream for binary write using the **ios::binary** flag.

.. code:: cpp

   ofstream particlesFile("particles.dat", ios::out | ios::binary);

To write particle data to the file we need create a variable to hold the
data to be written:

.. code:: cpp

   Particle p;

To write data to a binary file the **.write()** method takes a pointer
to a buffer of the data to write and the size of the buffer. To get a
size of a buffer we can use the **sizeof()** function in C++ to query
and variable for its size. In the following code we write 10 particles
to the binary file, **particles.dat**.

.. code:: cpp

   for (auto i = 0; i < 10; i++)
   {
       p.x = 100.0 * (double)rand() / (double)RAND_MAX;
       p.y = 100.0 * (double)rand() / (double)RAND_MAX;
       p.mass = 1.0 + (double)rand() / (double)RAND_MAX;

       particlesFile.write((char*)&p, sizeof(p));
   }
   particlesFile.close();

Please note that we reuse the same variable with different data for each
write, which is not always the case. The **.write()**-method requires a
char pointer, which is why we need the cast **p** before passing it in
the call. Also **p** is a local variable (on the stack), which is the
reason we pass it as reference using the **&** operator.

When writing to a binary file the invisible file pointer is moved the
size of the data writting every time you call the **.write()**-method.

Reading data from a binary file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Reading data is very similar to writing data, except now we read from
the file using the **.read()**-method and write data to a buffer of the
right size. Be default the file pointer will be placed at the beginning
of the file. In the following code a file object is opened for reading
using the **ios::binary** flag.

.. code:: cpp

   ifstream inputParticlesFile("particles.dat", ios::in | ios::binary);

   if (inputParticlesFile.is_open())
   {
       while (inputParticlesFile.good())
       {
           inputParticlesFile.read((char*)&p, sizeof(p));
           cout << "x = " << p.x;
           cout << ", y = " << p.y;
           cout << ", m = " << p.mass << endl;
       }
   }
   else
       cout << "Could not open file." << endl;

if we want to write more entries to the file at the end we can add the
**ios::ate** flag when opening the file. The file pointer is then moved
to the end of the file and the next entry written will be added after
the last buffer written to the file.

It is also possible to move the file pointer to the end of the file
using the **.seekg()**-method of the file stream object. The following
statement moves the file pointer to the beginning of the file. The first
argument is the offset to move from the position and direction given by
the second argument.

.. code:: cpp

   inputParticlesFile.seekg(0, ios::beg);

The second argument can be on of three alternatives

- **ios::beg** - search from the beginning of the file.
- **ios::cur** - search from the current position forward (+) and
  backwards (-).
- **iso::end** - search backwards from the end of the file.

If only a single argument is given to the **.seekg()**-method, this
argument is the absolute position in the file.

Reading elevations from a binary file
-------------------------------------

To illustrate real-world usage of how to read data from binary file, we
will open the the file **../data/colorado_elev.vit**, which contains
elevation values in a 400 x 400 image file. The first 268 bytes contains
a header, which we will need to skip. The rest of the data contains the
height values stored as unsigned bytes.

First we open the file for writing, also checking that the file was
opened.

.. code:: cpp

   ifstream infile;
   infile.open("../data/colorado_elev.vit", ios::in | ios::binary);

   if (!infile.is_open())
   {
       cout << "Error opening file" << endl;
       return 1;
   }

To be able to read the data from the file we need a buffer to store the
unsigned bytes into. In this case we use a **std::array** with 400 x 400
in size. An unsigned byte is defined as **uint8_t** in C++, which we
will use when we declare the array.

.. code:: cpp

   std::array<uint8_t, 400 * 400> buffer;

Now we need to move the file pointer to the correct position for reading
the elevation values in the file. We seek 268 bytes starting from the
beginning of the file.

.. code:: cpp

   infile.seekg(268, ios::beg);

Now we are in a position to be able to read the data. To read we use the
**.read()** method, which takes a pointer to a buffer and the size of
the buffer. The data in the **std::array** can be accessed by the
**.data()**-method, but needs to be cast to the correct pointer type. We
do this with the **reinterpret_cast()** function in C++. The size of the
buffer is returned by the **.size()**-method.

.. code:: cpp

   infile.read(reinterpret_cast<char*>(buffer.data()), buffer.size());

   infile.close();

This is everything required to read all the data from the binary file
into our **std::array**. To use the data we write it back to a text file
storing the data separated by commas (CSV).

To do this we open a output file stream.

.. code:: cpp

   fstream outfile;
   outfile.open("../data/colorado_elev.csv", ios::out);

   if (!outfile.is_open())
   {
       cout << "Error opening file" << endl;
       return 1;
   }

Next we loop over the data in the file and write it to a text file with
400 values per row. To be able to write our **uint8_t** values we need
to cast them to **int**. We do this with the **static_cast()** function.
The final code is shown below:

.. code:: cpp

   for (auto i = 0; i < 400; i++)
   {
       for (auto j = 0; j < 400; j++)
           outfile << static_cast<int>(buffer[i * 400 + j]) << ",";
       outfile << "\n";
   }

   outfile.close();

This file can be read and plotted in NumPy/Matplotlib with:

.. code:: py

   # Load data
   data = np.genfromtxt('colorado_elev.csv', delimiter=',')

   # Plot
   plt.figure()
   plt.contourf(data) 
   plt.title('Colorado')
   plt.savefig('colorado.png')

The resulting image is shown below:

.. raw:: html

   <figure>

.. raw:: html

   <figcaption>

Data from binary file.

.. raw:: html

   </figcaption>

.. raw:: html

   </figure>
