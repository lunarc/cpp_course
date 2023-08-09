# Data structures and algorithms

The C++ standard library contains many common data structures that are useful when implementing your application. Most of the data structures defined only support various basic functionality, instead algorithmic functionality is instead implemented separately and can work mostly with any data structures. Data structures are not type-specific and are implemented as template classes, supporting all builtin and user-defined data types.

The most common data structures in C++ are divided into the following different types:

* Array type structures (T is the data type)
    - std::vector<T\>
    - std::array<T\>
    - std::deque<T\>
* Linked list structures
    - std::list<T\>
* Stacks and queues
    - std::stack<T\>
    - std::queue<T\>
* Associative containers
    - std::map<Key, T\>
    - std::multimap<Key, T\>
    - std::set<Key\>
    - std::multiset<Key\>

## Data structures and iterators

To access and move through data structures C++ uses the concepts of an iterator. An iterator is a special type unique for each data structure that provides a way of moving through the elements in the data structure. It can be compared to the C++ pointer type, but with additional functionality. The value located where the iterator is positioned is accessed by dereferencing the iterator using the star operator (*).

Depending on the data structure the iterator can belong to different categories:

 * InputIterator - Can read and move forward. Only supports a single pass through the data structure.
 * ForwardIterator - Can read, move forward supporting multiple passes.
 * BidirectionalIterator - Can read, move forward and backwards.
 * RandomAccessIterator - An iterator can access any element in any order.
 * OutputIterator - Any of the above that support writing is considered a mutable iterator.

 To get a starting point for an iterator all data structures have a **.begin()** and **.end()** method. **.begin()** returns an iterator at the beginning of the data structure. **.end()** returns an iterator after the last item in the data structure. **.end()** is useful to be able to stop an iteration through a data structure, comparing the current iterator to the **.end()**-iterator. 

 To illustrate the use of iterators we use the **std::vector<T\>** as an example. **std::vector** is a data structure for storing values in a dynamically resizable array. First we declare and initialise the data structure.

```cpp
std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
```

This initializes the vector with some values. In the next step, we need to declare an iterator so that we can loop through the vector.

```cpp
std::vector<int>::iterator it;
```

Now we have all information to be able to iterate over the vector. To do this we use a standard loop statement. At the start of the loop, we initialize the iterator to the start iterator of the vector. We loop until **it** encounters the end iterator of the vector. For each iterator, we also need to move the iterator forward in the data structure using the **++** operator.

```cpp
for (it=v.begin; it!=v.end(); it++)
```

To access the actual value that corresponds to the current position of the iterator we can use the star operator (*).

```cpp
    cout << *it << "\n";
```

[:fontawesome-solid-gears: Try example](https://godbolt.org/z/sbTMab6v7){ .md-button  .target="_blank"}

If the data structure supports random access to the individual elements it is also possible to access the individual elements using the []-operator or the **.at()**-method. The **.at()**-method also supports bound checking.

```cpp
cout << v[0] << "\n";    // random acces to element 0 without bounds check.
cout << v.at(1) << "\n"; // radnom access to element 1 with bounds check.
```

We can simplify the code a bit using some of the more modern features of C++. First we don't have to specify the type of the vector if the element type can be deduced from the intialisation list.

```cpp
std::vector v = { 1, 2, 3, 4, 5 };
```

We also don't have to explicitly declare an iterator before the **for**-statement. The **auto**-keyword can be used as the iterator type can be deduced by the compiler.

```cpp
for (auto it=v.begin(); it!=v.end(); it++)
{
    cout << *it << "\n";
}
```

[:fontawesome-solid-gears: Try example](https://godbolt.org/z/rvYM6Yzzo){ .md-button  .target="_blank"}

## Range-based loops

To make it even easier iterate over data structure a new loop construct was introduced to the C++ language, the range-based loop. This construct is very similar to the way you iterate over data structures in Python. The syntax is simplifed:

```
for (named-variable : range-expression)
    loop-body
```

The *name-variable* is a variable of the same type as declared in the data structure to loop over. *range-expression* is the data structure that we will iterate over. A simple example iterating over a vector.

```cpp
std::vector vec = { 1, 2, 3, 4, 5 };

for (auto value : vec)
    std::cout << value << "\n";
```
[:fontawesome-solid-gears: Try example](https://godbolt.org/z/rMY87bEsq){ .md-button  .target="_blank"}

As we can see in the above example there is no need to use any iterators. In the following example **value** is copied from **vec**. If you have larger values in your data structures it is not efficient to copy the value in each iteration. To solve this the range-based loop can also be implemented using the reference operator (&). The code then becomes:

```cpp
std::vector vec = { 1, 2, 3, 4, 5 };

for (auto& value : vec)
    std::cout << value << "\n";
```

[:fontawesome-solid-gears: Try example](https://godbolt.org/z/aMTh88one){ .md-button  .target="_blank"}

In this implementation **value** is actually a reference to the value in **vec**. It is also possible to change the actual values of **vec** by assigning a value to **value**.

```cpp
std::vector vec = { 1, 2, 3, 4, 5 };

for (auto& value : vec)
    value = 0;

for (auto& value : vec)
    cout << value << "\n";
```
[:fontawesome-solid-gears: Try example](https://godbolt.org/z/G4GTh7cc1){ .md-button  .target="_blank"}

!!! note

    To be able to use the range-based for loop in C++ the data structure that you iterate over need to support iterators as this is the inner mechanics for the range-base loop.

## std::array<T, N\>

If the size of an array is known at compile time, it is often more effective to use a static array. However, the static C-based array in C++ is often harder to use with built-in algorithms and range-based loops as it lacks an easy way of querying the size of the array. To overcome this the **std::array** was introduced. This data structure combines the benefits of a C based static array with standard C++ container based data structure. To use the array we use the following include:

```cpp
#include <array>
```

To declare a **std::array** you have to specify a data type and the size of the array:

```cpp
std::array<float, 10> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
```

As this data structure is compatible with standard C++ containers it is possible to use a range-based for loop to iterate over the values.

```cpp
for (auto& value : arr)
    cout << value << "\n";
```

It is also possible to use C++ type deduction to automatically create an array without specifying data type and size.

```cpp
std::array arr = { 1.0f, 2.0f, 3.0f, 4.0f , 5.0f , 6.0f, 7.0f, 8.0f, 9.0f, 10.0f };
```

The size of an array can be queried using the **.size()** method.

```cpp
cout << "array size = " << arr.size() << "\n";
```
[:fontawesome-solid-gears: Try example](https://godbolt.org/z/Pr9KWKxoG){ .md-button  .target="_blank"}

**std::array** can also be used exactly as a normal array using the []-operator.

```cpp
for (auto i=0; i<arr.size(); i++)
    cout << arr[i] << "\n";
```
[:fontawesome-solid-gears: Try example](https://godbolt.org/z/9faqKnPYP){ .md-button  .target="_blank"}

Consider using **std::array** instead of static arrays whenever possible. If a pointer to an array is required it is always possible to use the **.data()** to get access to the pointer of the underlying array.

```cpp
auto* parr = arr.data();

for (auto i=0; i<10; i++)
    cout << parr[i] << "\n";
```

[:fontawesome-solid-gears: Try example](https://godbolt.org/z/b9nsqozfG){ .md-button .target="_blank"}



## std::vector<T>

## std::deque<T>

## std::list<T>

## std::map<Key, T>

## Algorithms

## Lambda functions





