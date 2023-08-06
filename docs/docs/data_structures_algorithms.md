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

[:fontawesome-solid-gears: Try example](https://godbolt.org/z/sbTMab6v7){ .md-button .md-button--primary .target="_blank"}

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

[:fontawesome-solid-gears: Try example](https://godbolt.org/z/rvYM6Yzzo){ .md-button .md-button--primary .target="_blank"}

## Range-based loops

## std::array<T>

## std::vector<T>

## std::deque<T>

## std::list<T>

## std::map<Key, T>

## Algorithms

## Lambda functions





