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

Another nice feature of the **std::array** is that you can use it with range-based loops as shown in the following example:

```cpp
for (auto &v : arr)
    std::cout << v << "\n";
```

Using range-based loops with arrays prevents errors where you access your arrays outside their defined range (bound checking errors).

[:fontawesome-solid-gears: Try example](https://godbolt.org/z/x34TcxvPd){ .md-button .target="_blank"}

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
<img src="../images/vector.svg" width="700px">
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

**std::deque** is similar to **std::vector**, linearly ordered, but supports efficiently adding and removing elements at the beginning and end. Compared to the **std::vector** no guarantees are given that the allocated data structure is contiguous. The advantage is that this data structure avoids large reallocations. 

The efficiency of the the different operations are as follows:

 * Directly accessing elements can be done in constant time - O(1).
 * Adding and removing elements at the beginning or end is achieved in constant time - O(1).
 * Inserting or removing elements at a specific position can be done in linear O(n) operations.

The conceptual data structure of **std::dequeue** is shown in the following figure:

<figure markdown>
<img src="../images/deque.svg" width="700px">
  <figcaption>std::deque data structure</figcaption>
</figure>

**std::deque** adds some additional methods for adding and removing items at the front and back of the datastructure:

* **.push_back(...)** - Adds an item at the end.
* **.pop_back(...)** - Removes an item from the end.
* **.push_front(...)** - Adds an item at the front.
* **.push_front(...)** - Remove an item at the front.

It is also possible to access the front and back elements using the methods **.front()** and **.back()**. Removing elements from the front and back can be done using the **.pop_front()** and **.pop_back()**. It is also possible to access element directly as in **std::vector** using the **[]**-operator and the **.as()**-method.

An example of how this is used is shown in the following code:

=== "Example"

    ``` cpp
    --8<-- "../ch_data_structures/deque1.cpp"
    ```

=== "Output"

    ```
    9, 8, 7, 6, 5, 0, 1, 2, 3, 4, 

    9, 8, 7, 6, 5, 0, 1, 2, 3, 4, 
    q front = 9
    pop front
    q front = 8
    q back = 4
    pop back
    q back = 3
    q[3] = 5
    ```

[:fontawesome-solid-gears: Try example](https://godbolt.org/z/4c6cGTGzP){ .md-button  .target="_blank"}

## std::list<T>

**std::list** is a linearly ordered data structure, implemented as a linked list. The data structure is especially efficient at adding and removing elements in the middle of the sequence. The disadvantage of **std::list** is that there is no direct access to elements. You will need to iterate through to access all elements. The data structure is well-suited for sorting algorithms. The conceptual data structure is shown in the figure below:

<figure markdown>
<img src="../images/list.svg" width="700px">
  <figcaption>std::list data structure</figcaption>
</figure>

Just as for the **std::deque** we have the following methods for adding items to the list:

* **.push_back(...)** - Adds an item at the end.
* **.pop_back(...)** - Removes an item from the end.
* **.push_front(...)** - Adds an item at the front.
* **.push_front(...)** - Remove an item at the front.

However, we don't have any []-operator or **.at()** method as this data structure does not allow direct access to its members. 

It is possible to add items to the list using the **.insert()** method. However, this requires an iterator position. We can iterate and insert at a certain position. Insert at the beginning is easy:

```cpp
l.insert(l.begin(), 42);
```

Insert at a certain position in this case before the value is 9.

```cpp
for (auto it = l.begin(); it != l.end(); it++)
{
    if (*it == 9)
        l.insert(it, 43); 
}
```

To remove items in the list we need to use an algorithm or use any of the class methods **.erase()**, **.remove()** or **.remove_if()**. 

Specific values in a list can be removed using the **.remove()** method:

```cpp
l.remove(5); // removes all elements with the value 5
```

Removing a specific element in the list is again done by iteration. Here we must be careful with the iterator so that we don't lose track of where to continue iteration. In the following example we delete all values that are equal to 3. We use the **.erase()** method to remove the iterator from the list, which moves and returns the iterator following the removed item. If the condition is not fulfilled we just move the iterator forward (++it). 

```cpp
for (auto it = l.begin(); it != l.end();)
{
    if (*it == 3)
        it = l.erase(it); // Returns next iterator after erase.
    else
        ++it;
}
```

!!! note

    Please note that we don't move the iterator forward in the **for**-statement to handle the situation when we remove the item from the list using the **.erase()** method.

A complete example of using the **std::list** is shown below:

=== "Example"

    ``` cpp
    --8<-- "../ch_data_structures/list1.cpp"
    ```

=== "Output"

    ```
    42, 10, 43, 9, 8, 7, 6, 0, 1, 2, 3, 4, 5, 
    42, 10, 43, 9, 8, 7, 6, 0, 1, 2, 3, 4, 5, 
    l front = 42
    pop front
    l front = 10
    l back = 5
    pop back
    l back = 4
    10, 43, 9, 8, 7, 6, 0, 1, 2, 3, 4, 
    10, 43, 9, 8, 7, 6, 1, 2, 3, 4, 
    10, 43, 9, 8, 7, 6, 1, 2, 4, 
    ```

[:fontawesome-solid-gears: Try example](https://godbolt.org/z/bn1zejqPE){ .md-button  .target="_blank"}


## std::map<Key, T>

In many applications it is desirable to store data associated with a key. The key can for example be a phone number or a name. Using the key it is possible to quickly access the data associated with the key. The **std::map** data structure stores unique keys with a single value per key. 

To declare a **std::map** datatyep you have to specify 2 data types one for the key and a second one for the value. In the following code we specify a map, **m**, with a string key and an integer value type.

```cpp
std::map<std::string, int> m;
```

Adding values to a map can be done by specifying a key using the []-operator and assigning a new value as shown below:

```cpp
m["bob"] = 42;
m["alice"] = 40;
m["mike"] = 30;
m["richard"] = 25;
```

If you assign to an already existing key the value is overwritten. It is also possible to use the **.insert()** method to insert values into the map:

```cpp
m.insert({"john", 84});
```

It is also possible to insert multiple entries using **.insert()**

```cpp
m.insert({"caroline", 94}, {"eva", 36});
```

One of the powerful aspect of a dictionary is the ability to quickly check for the existence of a key in a dictionary. **std::map** provides a method, **.find()**, that can query for a key. If a key is found an iterator is returned positioned at the key. If no key was found the method returns **.end()** iterator of the data structure. An example of this is shown below:

```cpp
it = m.find("carl");

if (it != m.end())
    std::cout << "found: " << it->first << ", " << it->second << "\n";
else
    std::cout << "Could not find Carl." << std::endl;
```

I the example above you can also see how you access the key and value of an iterator using the **->first** and **->second** accessors. 

In the same way as the other data structures iteration over the elements can be done using iterators. As shown in the following code:

```cpp
for (auto it = m.begin(); it != m.end(); it++)
    std::cout << it->first << ", " << it->second << "\n";
```

Using the new modern features of C++ we can also use the range based for-loop to iterate over the **std::map**. In the following example we use a single loop variable to access the key and values in the data structure.

```cpp
for (auto &item : m)
    std::cout << item.first << ", " << item.second << "\n"
```

Please note that now can use the dot-operator to access the **first** and **second** fields of the item variable. 

It is also possible to assign loop-variables for both the key as well as the value in a range-based loop.

```cpp
for (auto &[key, value] : m)
    std::cout << key << ", " << value << "\n";
```

This almost looks line the range-based loop in Python.

## Algorithms

Up until now, we have covered some of the data structures available in the C++ standard library. These classes contain methods for moving through the structure in different ways. However, they don't provide any algorithms for searching or querying the data structures. In C++ there is a distinct separation between data structures and algorithms. This gives you the freedom to use any algorithm on any data structure. Algorithms in C++ are provided through **<algorithm\>** header. The functions in this library can work with any data structure that provides **.first** and **.last** attributes.

### Lambda functions

Many of the algorithms provided in the standard library require a function to be provided for customising the behavior. To be able to use them you need to implement a function in C++ for each time you need to use the algorithm, which can be a bit complicated. To solve this problem C++ 11 introduced the concept of lambda functions. A lambda function is an anonymous function declaration that can be directly passed to a function call, without having to declare a named function in your source code. The simplified syntax is as follows:

> [capture clause] (parameters) -> return type { body }

The *capture clause* describes how the lambda functions should interact with variables outside the lambda function. By default, no interaction is specified. If an empty capture close is given, the lambda function can't interact with any variables. If an equal sign [=] is given the lambda function can access all variables by value. If [&] is given all variables are passed by reference to the lambda function. Specific variables can be specified by name or by value using the normal conventions in C++. The *parameters* section defines the input arguments of a function. This works just like a normal function declaration in C++. The *return type* is an optional part that can be left out, but it can be specified to make it more explicit what the function returns. The last part of the lambda function is the actual function *body* that implements the function. 

A lambda function can be passed directly to a function or declared directly in the code. In the following example, a lambda function **f** is declared using the **auto** directive. The lambda function can then be called just like any other function:

```cpp
auto f = [](int x) { return x * x; };
std::cout << f(5) << std::endl;
```

The function in this example takes **int** x as input and returns and **int**. The function can also be specified with a return type as shown in the following example:

```cpp
auto f = [](int x) -> int { return x * x; };
std::cout << f(5) << std::endl;
```

In the next example, we declare a function **g** that has a capture clause [=], which enables the function to access all variables outside the lambda function by value.

```cpp
int c = 42;

auto g = [=](int x) { return x * x + c; };
std::cout << g(5) << std::endl;
```

Accessing variables by references is achieved similarly in the following example:

```cpp
int c = 42;

auto h = [&](int x) { return x * x + c; };
std::cout << h(5) << std::endl;
```

If the lambda function should only access specific variables they can be specified in explicetly in the capture clause as in this example:

```cpp
int c = 42;

auto p = [&c](int x) -> int { return x * x + c; };
std::cout << p(5) << std::endl;
```

Here, the variable **c** is accessed by reference in the lambda function. 

Lambda functions in C++ are a very important concept that we will be using extensively in the following sections on algorithms. They provide a way of quickly providing additional functionality to the algorithms. 

### Sorting

Sorting is a very common operation on data structures. C++ provides the **std::sort()** function for sorting. The function takes an iterator for the starting position and an iterator for the end position. By default it sorts in ascending order compared with the less than operator (<), but it is also possible to supply your own comparison function. It is in this scenario where lambda functions provide a quick and easy way of specifying a comparison function.

In the following example, we use the **std::sort()** function in C++ to sort two arrays, providing our own comparison function as a named lambda function and as an anonymous function directly in the call to **std::sort()**. The requirement for comparison is a function that takes two input variables and returns true or false depending on the result of the comparison operation. Using this we can create our custom function that determines the sorting order of the algorithm.

```cpp
std::vector v1 = { 6, 4, 7, 3, 9, 0, 1, 5 };
std::vector v2 = { 6, 4, 7, 3, 9, 0, 1, 5 };

auto greater_func = [](int a, int b) -> bool { return a > b; };

std::sort(v1.begin(), v1.end(), greater_func);
std::sort(v2.begin(), v2.end(), [](int a, int b) -> bool { return a < b; });
```







### Finding

### Iterating with for_each

### Copying

### Removing elements

### Reduction operations

### Filling

### Creating ranges of values






