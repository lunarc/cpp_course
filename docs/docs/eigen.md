# Arrays computing with Eigen

Arrays are an important part in any scientific computing applications. As C++ is an object oriented language it is sometimes tempting to implement your own matrix library. However, this is often not a good idea as there are many libraries available that are well tested and optimized. One of the most popular libraries for linear algebra is Eigen. Eigen is a header only library that is easy to use and is very fast. Eigen also supports many of the optimised basic linear algebra packages such as BLAS and LAPACK, which really can speed up your computations. In this section we will cover the basics of Eigen and how to use it in your applications.

## Using the Eigen library

To use Eigen in your own application you first have to include the Eigen header file. Eigen is a header only library so you don't have to link against any libraries. To include Eigen in your application you can use the following code:

```cpp
#include <Eigen/Dense>
```

This includes the dense matrix module of Eigen. There are other modules, but we will cover them later. The `Eigen/Dense` module includes all the basic matrix operations and is the most commonly used module.

All Eigen classes are defined in the `Eigen` namespace. This means that you have to use the `Eigen::` prefix when using Eigen classes. For example, to define a 3x3 matrix you can use the following code:

```cpp
Eigen::Matrix3d A;
```

This declares a 3x3 matrix using double as the data type for storing individiual elements. When you declare a matrix like this, Eigen does not initialize the matrix. This means that the matrix will contain random values. Printing this matrix will give you something like this:

```cpp
std::cout << A << std::endl;
```

```text
-9.25596e+61 -9.25596e+61 -9.25596e+61
-9.25596e+61 -9.25596e+61 -9.25596e+61
-9.25596e+61 -9.25596e+61 -9.25596e+61
```

If you want to initialize the matrix you can use the following **.setZero()** method:

```cpp
A.setZero();
```

This will initialise the matrix to zero. You can also use the **.setOnes()** method to initialise the matrix to one. There are many other methods available to initialize the matrix. You can find them in the Eigen documentation.

### Initialising matrices

It is also possible to intialise the matrix using lists of values using the **<<** operator. For example, to initialise a 3x3 matrix to the identity matrix you can use the following code:

```cpp
Eigen::Matrix3d B;

D << 1, 2, 3,
     4, 5, 6,
     7, 8, 9;
```

Please not tha you only use the **<<** operator once followed by a comma separated list of values. The values are inserted row by row. If you want to insert a column vector you can use the **.col()** method. For example, to insert a column vector you can use the following code:

```cpp
D.col(0) << 1, 2, 3;
D.col(1) << 4, 5, 6;
D.col(2) << 7, 8, 9;
```

The matrix class also support inserting values by rows using the **.row()** method. For example, to insert a row vector you can use the following code:

```cpp
D.row(0) << 1, 2, 3;
D.row(1) << 4, 5, 6;
D.row(2) << 7, 8, 9;
```
**Matrix3d** and similar declarations are actually type definitions of the form **Matrix<double, 3, 3\>**. This means that you can also declare a matrix using the following code:

```cpp
Eigen::Matrix<double, 3, 3> E;
```

The first argument is the datatype and the second and third arguments are the number of rows and columns respectively. This is useful if you want to use a different datatype or if you want to use a dynamic number of rows and columns. 

### Dynamic size matrices

It is also possible to have arrays that can be resized in different or all dimensions. This can be accomplished by using the **Dynamic** keyword instead of the rows or columns sizes in the template type. For example, to declare a dynamic size matrix you can use the following code:

```cpp
Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> F;
```

Before using this array it has to be given a size. This can be done either directy when declaring the array variable or later using the **.resize()** method. For example, to declare a 3x3 matrix you can use the following code:

```cpp
Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> G(3, 3);
```

or

```cpp
Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> H;
H.resize(3, 3);
```

Just like the fixed size arrays the data in the array is not initialized. You can initialize the array using the initialisation methods mentioned above. If the resize operation does not change the number of elements in the array the data is preserved and the operation is very fast. If the number of elements is changed the data is lost and the operation is slower. The following example illustrates this:

```cpp
Matrix<double, Dynamic, Dynamic> A_dyn(3, 3); // Shorthand for MatrixXd

A_dyn << 1, 2, 3,
         4, 5, 6,
         7, 8, 9; 

cout << "Here is the matrix A_dyn:\n" << A_dyn << endl;

A_dyn.resize(1, 9); // No reallocation

cout << "Here is the matrix A_dyn after resizing:\n" << A_dyn << endl;

A_dyn.resize(6, 6); // Reallocation.

cout << "Here is the matrix A_dyn after resizing:\n" << A_dyn << endl;

A_dyn.setZero();

cout << "Here is the matrix A_dyn after setting to zero:\n" << A_dyn << endl;
```

This will output:

```text
Here is the matrix A_dyn:
1 2 3
4 5 6
7 8 9
Here is the matrix A_dyn after resizing:
1 4 7 2 5 8 3 6 9
Here is the matrix A_dyn after resizing:
-6.27744e+66 -6.27744e+66 -6.27744e+66 -6.27744e+66 -6.27744e+66 -6.27744e+66
-6.27744e+66 -6.27744e+66 -6.27744e+66 -6.27744e+66 -6.27744e+66 -6.27744e+66
-6.27744e+66 -6.27744e+66 -6.27744e+66 -6.27744e+66 -6.27744e+66 -6.27744e+66
-6.27744e+66 -6.27744e+66 -6.27744e+66 -6.27744e+66 -6.27744e+66 -6.27744e+66
-6.27744e+66 -6.27744e+66 -6.27744e+66 -6.27744e+66 -6.27744e+66 -6.27744e+66
-6.27744e+66 -6.27744e+66 -6.27744e+66 -6.27744e+66 -6.27744e+66 -6.27744e+66
Here is the matrix A_dyn after setting to zero:
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
```

As you can observe, as long as the number of elements in the array is not changed the data is preserved. If the number of elements is changed the data is lost and have to be reinitialized.

### Vectors

Just like the Matrix class Eigen also has a Vector class. The Vector class is a special case of the Matrix class where the number of rows or columns is fixed to 1. For example, to declare a 3x1 vector you can use the following code:

```cpp
Eigen::Vector3d v;
```

Initialising values can be done by specifying values in the constructor.

```cpp
Eigen::Vector3d v(1, 2, 3);
```

You can also use the **<<** operator to initialise the vector.

```cpp
Eigen::Vector3d w;
w << 1, 2, 3;
```

Intialisation is done using the same intialisation methods as the Matrix class.

```cpp	
Eigen::Vector3d x;
x.setZero();
```

The Vector classes are also based on the generic template type **Vector<Type, Size\>**. This means that the following code is equivalent to the previous code:

```cpp
Eigen::Vector<double, 3> y;
```

The Vector class also supports dynamic sizes. This can be specified by using the **Dynamic** keyword instead of the size in the template type. For example, to declare a dynamic size vector you can use the following code:

```cpp
Eigen::Vector<double, Eigen::Dynamic> z(3);
```

or

```cpp
Eigen::Vector<double, Eigen::Dynamic> z;
z.resize(3);
```

There is also a specialised version of the **Vector** class called **RowVector**. This class is a special case of the **Vector** class where the number of rows is fixed to 1. For example, to declare a 1x3 row vector you can use the following code:

```cpp
Eigen::RowVector3d r(1.0, 2.0, 3.0);
std::cout << r << std::endl;

Eigen::Vector3d s(1.0, 2.0, 3.0);
std::cout << s << std::endl;
```

This will output:

```text
1 2 3
1
2
3
```

### Convenience typedefs for Eige vectors and matrices

There are several convenience typedefs for fixed-size vectors and matrices. For example, **Vector3d** is a typedef for **Vector<double, 3\>** and **Matrix3d** is a typedef for **Matrix<double, 3, 3\>**. These typedefs are available for sizes 1 to 4. For larger sizes you have to use the generic template type. Below are listed some of the most common typedefs:

```cpp
typedef Matrix<double, 2, 2> Matrix2d;
typedef Matrix<double, 3, 3> Matrix3d;
typedef Matrix<double, 4, 4> Matrix4d;
typedef Matrix<double, 6, 6> Matrix6d;
typedef Matrix<double, Dynamic, Dynamic> MatrixXd;

typedef Matrix<float, 2, 2> Matrix2f;
typedef Matrix<float, 3, 3> Matrix3f;
typedef Matrix<float, 4, 4> Matrix4f;
typedef Matrix<float, 6, 6> Matrix6f;
typedef Matrix<float, Dynamic, Dynamic> MatrixXf;

typedef Matrix<int, 2, 2> Matrix2i;
typedef Matrix<int, 3, 3> Matrix3i;
typedef Matrix<int, 4, 4> Matrix4i;
typedef Matrix<int, 6, 6> Matrix6i;
typedef Matrix<int, Dynamic, Dynamic> MatrixXi;

typedef Vector<double, 2> Vector2d;
typedef Vector<double, 3> Vector3d;
typedef Vector<double, 4> Vector4d;
typedef Vector<double, 6> Vector6d;
typedef Vector<double, Dynamic> VectorXd;

typedef Vector<float, 2> Vector2f;
typedef Vector<float, 3> Vector3f;
typedef Vector<float, 4> Vector4f;
typedef Vector<float, 6> Vector6f;
typedef Vector<float, Dynamic> VectorXf;

typedef Vector<int, 2> Vector2i;
typedef Vector<int, 3> Vector3i;
typedef Vector<int, 4> Vector4i;
typedef Vector<int, 6> Vector6i;
typedef Vector<int, Dynamic> VectorXi;
```

## Matrix expressions

In the Eigen Matrix classes most normal C++ operators are overloaded, so that you perform linear algebra operations in a natural way. For example, you can add two matrices using the **+** operator:

```cpp
Matrix3d A;

A << 1, 2, 3,
     4, 5, 6,
     7, 8, 9;

Matrix3d B;

B << 1, 2, 3,
     4, 5, 6,
     7, 8, 9;

auto C = A + B;
cout << C << endl;
```

This outputs:

```text
 2  4  6
 8 10 12
14 16 18
```

For matrix and vector classes you can only perform linear algebra expressions. This means that you can only add matrices of the same size or multiply a matrix with a vector of the correct size. You can also multiply matrices with each other. Multiplying a matrix with a scalar is also possible, but adding a scalar to a matrix is not possible. The following code illustrates some of these operations:

```cpp
auto D = A * 3.0;
cout << D << endl;

auto E = A * B;
cout << E << endl;
```

which produces the following output:

```text
 3  6  9
12 15 18
21 24 27
 30  36  42
 66  81  96
102 126 150
```

If you want to add a scalar to all element you can use the following code:

```cpp
auto F = E + Matrix3d::Constant(1.0);   
cout << F << endl;
```

This will add 1.0 to all elements in the matrix. The **Constant()** method is a static method that creates a matrix with all elements set to the specified value. The **Array** class is a special class that allows you to perform element wise operations. Elementwise addition of a scalar can be done using the following code:

```cpp
Matrix3d G = E.array() + 3.0;
```

Here we use the **.array()** method to convert the matrix to an array. This enables us to use element addition to a scalar. If we then assign the result to a matrix the result is a matrix with the same size as the original matrix. 

## Matrix operations

Eigen has many special methods for matrices. For example, you can transpose a matrix using the **.transpose()** method. The following code illustrates this:

```cpp
Matrix3d H;

H << 1, 2, 3,
     4, 5, 6,
     7, 8, 9;

std::cout << "H^T = " << std::endl << H.transpose() << std::endl;
```

This produces the following output:

```text
H^T =
1 4 7
2 5 8
3 6 9
```

It is also possible to compute the dot product and cross product or matrices using the **.dot()** and **.cross()** methods. The following code illustrates this:

```cpp
Vector3d s(1, 2, 3);
Vector3d t(1, 0, 0);

auto u = s.cross(t);
auto p = s.dot(t);

cout << u << endl;
cout << p << endl;
```

This produces the following output:

```text
 0
 3
-2
1
```

It is also possible to compute the inverse of a matrix using the **.inverse()** method. The following code shows how this is done.

```cpp
Matrix3d J;

J << 15, 42, 71,
     23, 52, 81,
     33, 63, 91;

cout << J.inverse() << endl;
```

This produces the following output:

```text
 2.29012 -4.01852  1.79012
-3.58025  6.03704 -2.58025
 1.64815 -2.72222  1.14815
```

Some other useful function are reduction operations such as **.sum()**, **.mean()**, **.minCoeff()**, **.maxCoeff()** and **.norm()**. The following code illustrates how these functions are used:

```cpp
Matrix3d K;

K << 1, 2, 3,
     4, 5, 6,
     7, 8, 9;

cout << "K.sum()\n" << K.sum() << endl;
cout << "K.prod()\n" << K.prod() << endl;
cout << "K.mean()\n" << K.mean() << endl;
cout << "K.norm()\n" << K.norm() << endl;
cout << "K.maxCoeff()\n" << K.maxCoeff() << endl;
cout << "K.minCoeff()\n" << K.minCoeff() << endl;
cout << "K.trace()\n" << K.trace() << endl;
cout << "K.diagonal()\n" << K.diagonal() << endl;
cout << "K.determinant()\n" << K.determinant() << endl;
```

This produces the following output:

```text
K.sum()
45
K.prod()
362880
K.mean()
5
K.norm()
16.8819
K.maxCoeff()
9
K.minCoeff()
1
K.trace()
15
K.diagonal()
1
5
9
K.determinant()
0
```

There are many more matrix methods available in Eigen. You can find them in the Eigen documentation.

## Reshaping matrices

## Slicing and indexing

## Accessing raw data

## Using Eigen with other libraries

## Summary



