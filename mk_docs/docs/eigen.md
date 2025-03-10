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

Some times existing matrices must be used in expressions where the current shape of the matrix is not suitable. In these cases it is possible to reshape the matrix using the **.reshaped()** method. The following code illustrates how this is done:

```cpp
Matrix3d A;

A << 1, 2, 3,
    4, 5, 6,
    7, 8, 9;

auto B = A.reshaped(1, 9);

cout << B << endl;
```

I this example we have a 3x3 matrix that we want to reshape into a 1x9 matrix. The **.reshaped()** method takes two arguments. The first argument is the number of rows and the second argument is the number of columns. The B variables in the above example is actually a special class Eigen::Reshaped<> that is a view into the original matrix. This means that the data is not copied and that the reshaped matrix is a view into the original matrix. This also means that if you change the reshaped matrix the original matrix is also changed. 

Running the previous code produces the following output:

```text
1 2 3 4 5 6 7 8 9
```

If we want to use the **B** matrix to assign a new matrix the matrix to be assigned needs to be of the **MatrixXd** type. In the following code we assign the reshaped matrix to a new matrix:

```cpp
MatrixXd C = B.reshaped(3, 3);

cout << C << endl;
```

This produces the following output:

```text
1 2 3
4 5 6
7 8 9
```

We can also reshape the created matrix and transpose it. The following code illustrates this:

```cpp
MatrixXd D = C.reshaped(1, 9).transpose();

cout << D << endl;
```

This produces the following output:

```text
1
4
7
2
5
8
3
6
9
```

Notice the ordering of numbers. This is due to the fact that matrices are stored in column major order in Eigen. This means that the first column is stored first, then the second column and so on. This is the opposite of row major order where the first row is stored first, then the second row and so on.

Assigning a reshaped matrix to itself is not allowed in Eigen. To solve this you can use the **.eval()** method. The **.eval()** method forces the reshaped matrix to be evaluated and copied to a new matrix. The following code illustrates this:

```cpp
C = C.reshaped(1, 9).eval();
```

## Slicing and indexing

One of the more common operations in matrix computing is indexing and slicing. Eigen has several ways of doing this. The easiest way of accessing rows and columns of a matrix in Eigen is using the **.row()** and **.col()** methods. The methods can be both used to assign values to a row or assign other matrices the values of a row. The following code illustrates this:

```cpp
MatrixXd A(10, 10);
A.setZero();

A.row(3) << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;

cout << A << endl;
cout << "\n";

A.col(3) << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;

cout << A << endl;
cout << "\n";
```

This produces the following output:

```text
 0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0
 1  2  3  4  5  6  7  8  9 10
 0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0  0  0

 0  0  0  1  0  0  0  0  0  0
 0  0  0  2  0  0  0  0  0  0
 0  0  0  3  0  0  0  0  0  0
 1  2  3  4  5  6  7  8  9 10
 0  0  0  5  0  0  0  0  0  0
 0  0  0  6  0  0  0  0  0  0
 0  0  0  7  0  0  0  0  0  0
 0  0  0  8  0  0  0  0  0  0
 0  0  0  9  0  0  0  0  0  0
 0  0  0 10  0  0  0  0  0  0
```

In this example we used the **<<** operator to assign values to the rows. 

It is also possible to assign multiple values at the same time using for example the .setConstant() or .setOnes() methods. The following code illustrates this:

```cpp
A.col(1).setOnes();

cout << A << endl;
cout << "\n";
```

This produces the following output:

```text
 0  1  0  1  0  0  0  0  0  0
 0  1  0  2  0  0  0  0  0  0
 0  1  0  3  0  0  0  0  0  0
 1  1  3  4  5  6  7  8  9 10
 0  1  0  5  0  0  0  0  0  0
 0  1  0  6  0  0  0  0  0  0
 0  1  0  7  0  0  0  0  0  0
 0  1  0  8  0  0  0  0  0  0
 0  1  0  9  0  0  0  0  0  0
 0  1  0 10  0  0  0  0  0  0
```

Indexing can also be done using the special function Eigen::seq(). In its simplest form it can be used to select a range of values. The following code illustrates this:

```cpp
MatrixXd B(10, 10);
B.setZero();

B(seq(3, 5), seq(3, 5)).setConstant(1);

cout << B << endl;
```

This produces the following output:

```text
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 1 1 1 0 0 0 0
0 0 0 1 1 1 0 0 0 0
0 0 0 1 1 1 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
```

It is also possible to use a step value in the **seq()** function, which is shown in the following code:

```cpp
B(seq(0, 9, 2), seq(0, 9, 2)).setConstant(2);

cout << B << endl;
```

This produces the following output:

```text
2 0 2 0 2 0 2 0 2 0
0 0 0 0 0 0 0 0 0 0
2 0 2 0 2 0 2 0 2 0
0 0 0 1 1 1 0 0 0 0
2 0 2 1 2 1 2 0 2 0
0 0 0 1 1 1 0 0 0 0
2 0 2 0 2 0 2 0 2 0
0 0 0 0 0 0 0 0 0 0
2 0 2 0 2 0 2 0 2 0
0 0 0 0 0 0 0 0 0 0
```

There are also special selectors for selecting rows and columns. The **all** selector selects all rows or columns. The **last** selector selects the last column or row. The following code illustrates this:

```cpp
B(all, last).setConstant(3);

cout << B << endl;
cout << "\n";

B(all, last - 1).setConstant(4);

cout << B << endl;
```

This produces the following output:

```text
2 0 2 0 2 0 2 0 2 3
0 0 0 0 0 0 0 0 0 3
2 0 2 0 2 0 2 0 2 3
0 0 0 1 1 1 0 0 0 3
2 0 2 1 2 1 2 0 2 3
0 0 0 1 1 1 0 0 0 3
2 0 2 0 2 0 2 0 2 3
0 0 0 0 0 0 0 0 0 3
2 0 2 0 2 0 2 0 2 3
0 0 0 0 0 0 0 0 0 3

2 0 2 0 2 0 2 0 4 3
0 0 0 0 0 0 0 0 4 3
2 0 2 0 2 0 2 0 4 3
0 0 0 1 1 1 0 0 4 3
2 0 2 1 2 1 2 0 4 3
0 0 0 1 1 1 0 0 4 3
2 0 2 0 2 0 2 0 4 3
0 0 0 0 0 0 0 0 4 3
2 0 2 0 2 0 2 0 4 3
0 0 0 0 0 0 0 0 4 3
```

It is also possible to use std::vector based indeces to select a submatrix from a matrix. This is shown in the following code:

```cpp
vector<int> idx = { 1, 3, 4, 6, 7, 9 };

cout << C(idx, idx) << endl;
cout << "\n";

auto D = C(idx, idx);
```	

This produces the following output:

```text
  1  11  21  31  41  51  61  71  81  91
  2  12  22  32  42  52  62  72  82  92
  3  13  23  33  43  53  63  73  83  93
  4  14  24  34  44  54  64  74  84  94
  5  15  25  35  45  55  65  75  85  95
  6  16  26  36  46  56  66  76  86  96
  7  17  27  37  47  57  67  77  87  97
  8  18  28  38  48  58  68  78  88  98
  9  19  29  39  49  59  69  79  89  99
 10  20  30  40  50  60  70  80  90 100

 12  32  42  62  72  92
 14  34  44  64  74  94
 15  35  45  65  75  95
 17  37  47  67  77  97
 18  38  48  68  78  98
 20  40  50  70  80 100
```

## Implementing functions with Eigen

There are some considerations to think about when passing matrices and vector to methods and functions. The general rule is to always pass Eigen matrices and vectors by reference. The exception to this rule is when returning a matrix or vector from a function. In this case you should return the matrix or vector by value. In the following example we have a function that creates a matrix given some non-matrix input:

```cpp
enum TAnalysisType {PLANE_STRESS, PLANE_STRAIN};

MatrixXd hooke(TAnalysisType ptype, double E, double v)
{
    MatrixXd D;
    switch (ptype) {
        case PLANE_STRESS:
            D.resize(3,3);
            D << 1.0, v,   0.0,
                 v,   1.0, 0.0,
                 0.0, 0.0, (1.0-v)*0.5;
            break;
        case PLANE_STRAIN:
            D.resize(4,4);
            D << 1.0-v, v    , v     , 0.0,
                 v    , 1.0-v, v     , 0.0,
                 v    , v    , 1.0-v , 0.0,
                 0.0  , 0.0  , 0.0   , 0.5*(1.0-2*v);
            break;
        default:
            break;
    }
    return D;
}

int main()
{
    MatrixXd Dpstress = hooke(PLANE_STRESS, 2.1e9, 0.35);
    MatrixXd Dpstrain = hooke(PLANE_STRAIN, 2.1e9, 0.35);
    
    cout << "D,pstress = " << endl;
    cout << Dpstress << endl;
    cout << "D,pstrain = " << endl;
    cout << Dpstrain << endl;
}
```

This produces the following output:

```text
D,pstress =
    1  0.35     0
 0.35     1     0
    0     0 0.325
D,pstrain =
0.65 0.35 0.35    0
0.35 0.65 0.35    0
0.35 0.35 0.65    0
   0    0    0 0.15
```

In the next example we have a function that takes **Vector<>** as inputs and returns a matrix.

```cpp
Matrix4d bar2e(const Vector2d& ex, const Vector2d& ey, const Vector2d& ep)
{
    double E = ep(0);
    double A = ep(1);
    double L = sqrt(pow(ex(1)-ex(0),2)+pow(ey(1)-ey(0),2));
    double C = E*A/L;
    
    Matrix2d Ke_loc(2,2);

    Ke_loc <<  C, -C,
              -C,  C;
    
    double nxx = (ex(1)-ex(0))/L;
    double nyx = (ey(1)-ey(0))/L;
    
    MatrixXd G(2,4);
    
    G << nxx, nyx, 0.0, 0.0,
         0.0, 0.0, nxx, nyx;
    
    Matrix4d Ke = G.transpose()*Ke_loc*G;
    return Ke;
}
```

Below is an example of how this function can be called:
  
```cpp
int main()
{
    VectorXd ex(2);
    VectorXd ey(2);
    VectorXd ep(2);
    
    ex << 0.0, 1.0;
    ey << 0.0, 1.0;
    ep << 1.0, 1.0;
    
    MatrixXd Ke = bar2e(ex, ey, ep);
    
    cout << Ke << endl;
}
```

Running the code produces the following output:

```text
 0.353553  0.353553 -0.353553 -0.353553
 0.353553  0.353553 -0.353553 -0.353553
-0.353553 -0.353553  0.353553  0.353553
-0.353553 -0.353553  0.353553  0.353553
```

## Solving linear systems of equations

Eigen has a library of decomposition methods that can be used to solve linear systems of equations. For smaller matrices (up to 4x4) it is often better to use the **.inverse()** method. For larger matrices it is better to use the decomposition methods. The following code illustrates how to solve a linear system of equations using the **.inverse()** method:

```cpp
int main()
{
    Matrix3d A;
    A.setRandom();

    Vector3d b;

    b.setRandom();

    Vector3d x = A.inverse() * b;

    cout << "The solution is:\n"
         << x << endl;

    cout << "b is:\n"
         << b << endl;

    cout << "A * x is:\n"
         << A * x << endl;

    cout << "The error is:\n"
         << (A * x - b).norm() << endl;
}
```

This produces the following output:

```text
The solution is:
 -1.36005
 -1.53203
-0.275723
b is:
  0.49321
-0.651784
 0.717887
A * x is:
  0.49321
-0.651784
 0.717887
The error is:
0
```

For larger matrices it is better to use the decomposition methods. Which decomposition method to chose is determined by your specific problem. The following code illustrates how to solve a linear system of equations using the **ColPivHouseholderQR** decomposition:

```cpp
int main()
{
    MatrixXd A(10, 10);
    A.setRandom();

    VectorXd b(10);
    b.setRandom();

    VectorXd x = A.colPivHouseholderQr().solve(b);

    cout << "The solution is:\n"
         << x << endl;

    cout << "b is:\n"
         << b << endl;

    cout << "A * x is:\n"
         << A * x << endl;

    cout << "The error is:\n"
         << (A * x - b).norm() << endl;
}
```

The key is the line:

```cpp
VectorXd x = A.colPivHouseholderQr().solve(b);
```

When calling the **.colPivHouseholderQr()** method on the matrix it returns a **ColPivHouseholderQR** object. This object has a **.solve()** method that can be used to solve the linear system of equations. The **.solve()** method takes a vector as input and returns a vector as output.

!!! note
    The **ColPivHouseholderQR** decomposition is a good choice for general matrices. For symmetric matrices the **LDLT** decomposition is a good choice. 

It is of couse also possible to explicitely create a **ColPivHouseholderQR** object and use it to solve the linear system of equations, which is shown below:

```cpp
FullPivLU<MatrixXd> ldlt(A);
VectorXd x = ldlt.solve(b);
```

!!! note
    The **FullPivLU** decomposition is a good choice for general matrices. For symmetric matrices the **LDLT** decomposition is a good choice.

The advantage of separating the construction from solving the system is that the decomposition can be reused for multiple systems. The **.solve()** method can also be called with a matrix as input. This will solve the system for each column in the matrix. As the following code illustrates:

```cpp
MatrixXd A(10, 10);
A.setRandom();

MatrixXd b(10, 10);
b.setRandom();

FullPivLU<MatrixXd> ldlt(A);
MatrixXd x = ldlt.solve(b);

cout << "The solution is:\n"
        << x << endl;
```

This produces the following output:

```text
The solution is:
   1.18453  -0.410319  -0.623361  -0.321932 -0.0895882  0.0497296  -0.648823   0.124508   0.493074   0.480588
  0.535632  0.0616908   -0.28512  -0.318507 0.00406816  0.0258458 -0.0848685  -0.477436    1.24756   0.838648
-0.0107144  -0.367311   0.244476   0.137709  -0.815272  -0.280075  -0.628219   0.208019  -0.206337  -0.640611
  -2.13074    1.62113 -0.0941863       1.03   -0.03775    1.03846   0.293851    1.14827   -3.90631   -1.16682
  0.879087   0.477271   -1.28075    1.28879    2.52322    -1.4507    1.27269  -0.578986    0.24615    2.08061
 -0.732436  -0.704311    1.06786  -0.596086    -2.3671    1.43309   -1.39648  0.0979355  -0.356579   -1.55783
  0.127638  -0.668733  -0.507232 -0.0496553   0.521617   0.220945   -0.16289  -0.664471    1.69368   0.876999
 -0.569963 -0.0353519  -0.507716  0.0109401   0.415603   0.829978  -0.209561  0.0241958  -0.291877 -0.0407887
  -2.30094    1.32775  -0.272818   0.388941   -0.53578    1.08094   0.510719   0.903556   -4.88332   -1.75593
   1.01693   0.242351  -0.251851   -1.13456    0.28466  -0.149436   -0.17369   0.721883   0.108984  0.0144817
```
### Returning Matrices from functions

### Passing Matrices to functions




## Accessing raw data

## Using Eigen with other libraries

## Summary



