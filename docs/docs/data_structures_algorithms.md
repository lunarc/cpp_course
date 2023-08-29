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

**std::vector** is a linear data structure that can expand when a certain capacity is reached. It is very similar to the **std::array** data structure, but the size is not fixed. The data structure can be accessed with iterators as well as direct access using the []-operator. Elements can be added by using the method **.push_back()**. The efficiency of the the different operations are as follows:

 * Directly accessing elements can be done in constant time - O(1).
 * Adding or removing element can be done in amortized constant time O(1). That is on average the operation can be completed in O(1) complexity.
 * Inserting or removing elements at a specific position can be done in O(n) operations.

Below is an example of an explicit declaration of a **std::vector**.

```cpp
std::vector<int> vec = { 1, 2, 3, 4, 5 };
```

It is also possible to skip the data type and let the compiler decide using deduction.

```cpp
std::vector vec = { 1, 2, 3, 4, 5 };
```

Elements can be added using the **.push_back()** method.

```cpp
vec.push_back(6);
vec.push_back(7);
```

A new method was added in C++11, **.emplace_back()**, which can be used if a new non-existent object should be added to the vector. This method avoids unnecessary copying that could occur otherwise. For the built-in data types, this difference is negligible, but for more complex data types this can improve performance significantly.

The size of the array can be queried using the **.size()** method.

```cpp
std::cout << vec.size() "\n";
```

We can iterate over the vector using both iterators and direct access loops. Iterating using a loop variable.

```
for (auto i=0; i<vec.size(); i++)
    std::cout << vec[i] << ", ";

std::cout << "\n";
```

Iterating using iterator is shown below:

```cpp
for (auto it=vec.begin(); it!=vec.end(); it++)
    std::cout << *it << ", ";

std::cout << "\n";
```

Finally, we can use a range-based for-loop as well:

```cpp
for (auto& v : vec)
    std::cout << v << ", ";

std::cout <<"\n";
```

[:fontawesome-solid-gears: Try example](https://godbolt.org/z/43ajYMM3r){ .md-button .target="_blank"}

Removing items from a vector can be done using the **.erase()** method, which takes an iterator as argument. The following code erases the first element:

```cpp
vec.erase(vec.begin());
```

In many cases you want to erase a specific element at a specific index. This can be done by adding an index value to an iterator as in this code which erases the second element.

```cpp
vec.erase(vec.begin()+1);
```

It is also possible to insert elements using the **.insert()** method. This methods takes an iterator as an argument for the position where the value should be inserted and the value that should be inserted. The following code inserts 42 at the third position in the list

```cpp
vec.insert(vec.begin()+2, 42);
```

The size of the vector can be changed using the **.resize()** method. If the new size is larger than the current size elements are added to the vector. If the new size is smaller existing elements will be erased.

A **std::vector** is not resized on all calls to **.push_back()**, usually the capacity is doubled every time capacity is exceeded. The current number of allocated elements in a vector can be queried using the **.capacity()** method. This value is often larger than **.size()**. 

If you know that a vector should be at least a certain number of elements it is possible to pre-allocate the number of elements using the **.reserve()** method. Note that this method does not change the size of the vector. There is also a special method for freeing up unused memory **.shrink_to_fit()** in the vector. 

The following figure illustrates how the **std::vector** works:

<figure markdown>
<img src="../images/vector.svg" width="500px">
  <figcaption>std::vector data structure</figcaption>
</figure>


All elements in a **std::vector** can be cleared using the **.clear()** method.  

```cpp
vec.clear();
```

A more complete example is shown below:

=== "Example"

    ``` cpp
    --8<-- "../ch_data_structures/vector1.cpp"
    ```

=== "Output"

    ```
    12637
    6149
    30314
    32595
    9916
    7874
    3554
    5407
    13053
    27214

    12637
    6149
    30314
    32595
    9916
    7874
    3554
    5407
    13053
    27214

    20108
    3184
    14168
    23442
    18432
    24466
    2492
    25169
    5702
    14458
    ```

[:fontawesome-solid-gears: Try example](https://godbolt.org/z/jqeqWe163){ .md-button  .target="_blank"}

[:fontawesome-solid-link: More info on std::vector (cppreference)](https://en.cppreference.com/w/cpp/container/vector){ .md-button .target="_blank"}


## std::deque<T>

## std::list<T>

## std::map<Key, T>

## Algorithms

## Lambda functions





