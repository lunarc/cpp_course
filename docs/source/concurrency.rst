Concurrency
===========

.. image:: images/concurrency.png
   :width: 100.0%

Concurrencey is the ability to run mutiple tasks simultaneously. This concept becomes more and more important as the number of cores in CPUs increases. In a single core CPU, the operating system can switch between tasks so fast that it appears that they are running simultaneously. However, in a multi-core CPU, the tasks can actually run simultaneously. As the clock frequencies of modern processor are not increasing as fast as they used to, the number of cores in CPUs is increasing. This means that in the future, the performance of a program will depend on how well it can utilize multiple cores. This is why concurency is important.

In C++ this can be acomplished using threads or processes. A process is an independent execution unit that has its own memory space. Processes are typically applications runing on your computer like a web browser or a text editor. Threads are similar to processes, but they share the same memory space. This means that threads can communicate with each other by reading and writing to the same memory locations. Threads are typically used for tasks that are closely related and need to share data. 

In  this chapter we are mainly going focus thread based concurrency. Before C++11 threads were not part of the standard library and you had to rely on platform specific libraries for this functionality. On Linux you mainly used the POSIX threads library (pthread) and on Windows you had to use the Windows API. 

C++11 introduced the `std::thread` class which is a part of the standard library. This class is used to create and manage threads. C++20 introduced the `std::jthread` class which is similar to std::thread, but it has some additional features which we will cover in the following sections.

Threading basics
----------------

The basic way of creating a thread is to create a thread object and pass a function to it. The passed function will be executed on the new thread. Here is an example:

.. tabs::

    .. tab:: Code

        .. code:: cpp

            #include <print>
            #include <thread>
            #include <chrono>

            void myfunc()
            {
                std::print("Thread {} starting.\n", std::this_thread::get_id());
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::print("Thread {} stopping.\n", std::this_thread::get_id());
            }

            int main()
            {
                std::jthread t(myfunc);
                t.join();
                std::println("Main thread stopping.\n");
            }

    .. tab:: Output
        
        .. code:: text

            Thread 37968 starting.
            Thread 37968 stopping.
            Main thread stopping.

.. button-link:: https://godbolt.org/z/xbcjhETaP
    :color: primary
    :outline:
    
    Try example

In the example above we have defined a function, `myfunc()` that prints its id and waits for a second and the prints that it is stopping. To executed this function on a thread, we create a `std::jthread` object `t` and pass the function to it. The thread will execute immediately when created. As the thread is executed concurrently the main routine can terminate before the thread function terminates, which can lead to undefined behavior. To solve this the thread object has special method, `.join()`, which can be used to wait for the thread to finish.

.. note::

    When working with threads and output, always use ``std::print()`` or ``std::println()`` from C++23 instead of ``std::cout``. The ``std::print`` family of functions are thread-safe and guarantee that output from different threads won't be interleaved. Using ``std::cout`` from multiple threads without synchronization can result in garbled output.

Managing Multiple Threads
-------------------------

To illustrate how threads can be used in computational tasks we will implement an algorithm calculating a sum of integers. 

.. math::

    \sum_{k=0}^{n} k

This has the closed-form solution of:

.. math::

    \sum_{k=0}^{n} k = \frac{n(n+1)}{2}

By having a closed-form solution we can also easily check the results of our algorithm. 

In our algorithm we need a function that can calculate a part of a sum in a range. We also want it to be able to store its sum somewhere. The following code shows how this function could be implemented.

.. code:: cpp

    void sum(const int a, const int b, const int id, long long *sums)
    {
        long long localSum = 0;

        for (int i = a; i <= b; i++)
            localSum += i;

        sums[id] = localSum;
    }

The ``sums`` array contains the sums for each separate calculcation. ``id`` is the index of the current calculation performed. Now we want to create a number of threads each performing a sum over a range in the total series. 

In our complete program we will use the ``std::print()`` function and ``std::vector`` for output and storing ``std::jthread`` and sums. To do this we need the following includes:

.. code:: cpp

    #include <thread>
    #include <vector>
    #include <print>

The first thing we will do in our main program is to define constants for our total range, that is from 0 to 100000000. As they will not change during the computation we declare them as ``const``.

.. code:: cpp

    const int a = 0;
    const int b = 100000000;    

Next, we need to determine how many threads we are going to use. To be useful we will use a minimum of 8 up to the total of threads possible in the system. To calculate this we will use the ``std::min()`` function combined with the ``std::thread::hardware_concurrency()`` method in the thread library. We declare a constant, ``numThreads``, which we assign the actual value. We also use the ``auto`` keyword so that we don't have to bother with the actual datatype returned from the ``std::min()`` function.

.. code:: cpp

    const auto numThreads = std::min(8u, std::thread::hardware_concurrency());

To be able to handle multiple threads we can use a ``std::vector`` to store the jthread instances in. We declare an array ``threads`` that will hold our created threads.

.. code:: cpp

    std::vector< std::jthread > threads;

To handle the individual sums that the threads will comput we will declare a ``std::vector``, ``sums`` for holding the results. We resize this vector to the number of threads being used.

.. code:: cpp

    std::vector< long long > sums;
    sums.resize(numThreads);    

Next, we will create some required constants for determining the ranges each thread will calculcate and som variables used in our thread creation loop.

.. code:: cpp

    const int chunkSize = (b - a + 1) / numThreads;
    const int remainder = (b - a + 1) % numThreads;

    std::print("Summing from {0} to {1} using {2} threads\n", a, b, numThreads);
    std::print("Chunk size = {0}, Remainder = {1}\n", chunkSize, remainder);

    int i0, i1;

In our thread creation loop we first calculcate ``i0`` and ``i1`` then we create our threads using the ``.emplace_back()`` method which will automatically call the thread constructor with the function pointer as well as the function arguments. The thread will immediately start executing the ``sum()`` function at this point.

.. code:: cpp

    for (auto i = 0; i < numThreads; i++)
    {
        i0 = a + chunkSize * i + std::min(i, remainder);
        i1 = i0 + chunkSize - 1;

        if (i < remainder)
            i1++;

        std::print("Thread {0}: i0 = {1}, i1 = {2} (count = {3})\n", i, i0, i1, i1 - i0 + 1);
        threads.emplace_back(sum, i0, i1, i, sums.data());
    }

We now have several threads running and computing our sum. Before we can calculate the total sum we need to make sure all threads have finished executing. This can be done using the ``.join()`` method on the ``jthread`` object. Waiting for all our threads can easily be done using another simple loop as shonw in the following code:

.. code:: cpp

    std::print("Waiting for completion...\n");

    for (auto& thread : threads)
        thread.join();    

This can look somewhat strange that we are sequentially waiting for the threads, but remember that the threads are executing concurrently and we need to wait for all of them. If the first thread we join take longer the other calls to the ``.join()`` method will return directly as the other threads have already completed.

We are now ready to compute our total sum and a comparison with the closed-form result using the following code:

.. code:: cpp

    long long totalSum = 0;
    auto i = 0;

    for (auto& sum : sums)
    {
        totalSum += sum;
        std::print("Sum {0} = {1}\n", i, sums[i++]);
    }

    std::print("Total sum = {0}\n", totalSum);
    
    long long expected = (long long)(b - a + 1) * (a + b) / 2;
    std::print("Expected sum = {0}\n", expected);
    std::print("Difference = {0}\n", totalSum - expected);    

.. note::

    The implementation of the current algorithm is considered thread safe as the sum function only write to a unique id in the ``sums`` vector. 

The complete code is shown below:

.. tabs::

    .. tab:: Example

        .. code:: cpp

            #include <thread>
            #include <vector>
            #include <print>

            void sum(const int a, const int b, const int id, long long *sums)
            {
                long long localSum = 0;

                for (int i = a; i <= b; i++)
                    localSum += i;

                sums[id] = localSum;
            }

            int main()
            {
                const int a = 0;
                const int b = 100000000;

                const auto numThreads = std::min(8u, std::thread::hardware_concurrency());

                std::vector< std::jthread > threads;

                std::vector< long long > sums;
                sums.resize(numThreads);
                
                const int chunkSize = (b - a + 1) / numThreads;
                const int remainder = (b - a + 1) % numThreads;

                std::print("Summing from {0} to {1} using {2} threads\n", a, b, numThreads);
                std::print("Chunk size = {0}, Remainder = {1}\n", chunkSize, remainder);

                int i0, i1;

                for (auto i = 0; i < numThreads; i++)
                {
                    i0 = a + chunkSize * i + std::min(i, remainder);
                    i1 = i0 + chunkSize - 1;

                    if (i < remainder)
                        i1++;

                    std::print("Thread {0}: i0 = {1}, i1 = {2} (count = {3})\n", i, i0, i1, i1 - i0 + 1);
                    threads.emplace_back(sum, i0, i1, i, sums.data());
                }

                std::print("Waiting for completion...\n");

                for (auto& thread : threads)
                    thread.join();

                long long totalSum = 0;
                auto i = 0;

                for (auto& sum : sums)
                {
                    totalSum += sum;
                    std::print("Sum {0} = {1}\n", i, sums[i++]);
                }

                std::print("Total sum = {0}\n", totalSum);
                
                long long expected = (long long)(b - a + 1) * (a + b) / 2;
                std::print("Expected sum = {0}\n", expected);
                std::print("Difference = {0}\n", totalSum - expected);

                return 0;
            }

    .. tab:: Output

        .. code:: 

            Summing from 0 to 100000000 using 8 threads
            Chunk size = 12500000, Remainder = 1
            Thread 0: i0 = 0, i1 = 12500000 (count = 12500001)
            Thread 1: i0 = 12500001, i1 = 25000000 (count = 12500000)
            Thread 2: i0 = 25000001, i1 = 37500000 (count = 12500000)
            Thread 3: i0 = 37500001, i1 = 50000000 (count = 12500000)
            Thread 4: i0 = 50000001, i1 = 62500000 (count = 12500000)
            Thread 5: i0 = 62500001, i1 = 75000000 (count = 12500000)
            Thread 6: i0 = 75000001, i1 = 87500000 (count = 12500000)
            Thread 7: i0 = 87500001, i1 = 100000000 (count = 12500000)
            Waiting for completion...
            Sum 1 = 78125006250000
            Sum 2 = 234375006250000
            Sum 3 = 390625006250000
            Sum 4 = 546875006250000
            Sum 5 = 703125006250000
            Sum 6 = 859375006250000
            Sum 7 = 1015625006250000
            Sum 8 = 1171875006250000
            Total sum = 5000000050000000
            Expected sum = 5000000050000000
            Difference = 0            

.. button-link:: https://godbolt.org/z/6Eaq6vGE6
    :color: primary
    :outline:
    
    Try example

Synchronization and Mutexes
---------------------------

We have now covered some basic usage of threads in C++. The examples shown have been well-behaved, not writing to the same memory locations and not shared any information between threads. What happens if threads are accessing the same memory locations or variables? If threads are only reading data from shared resources are usually not a problem. The problems come when they are going to write data in the same location. You can have multiple threads running concurrently that needs to update a counter at the same time. The update operation reading, modifying and writing back can not be acomplished atomically. That is a one thread can read at the same time as another thread writes resulting in an unknown variable state. To handle this situation we need to be able to synchronise access to the shared resource. This can be done using mutexes in C++. A mutex is an object that only one thread at a time can access. It works like a lock. When a thread wants to access a resource it calls the ``.lock()`` method on the mutex, which "locks" access to the resource until the thread calls ``.unlock()`` method. If another thread has locked the mutex the ``.lock()`` method will block and wait until it is available. Preventing the thread from mosifying the shared resource. 

``std::mutex`` should not be used directly as it is not exception safe. If an exception is thrown inside the code between ``.lock()`` and ``.unlock()`` calls will lead that the mutex will be locked forever. To solve this, mutexes should always be used together with a so called lock guard (``std::lock_guard``). This is a special class that owns a mutex and automatically calls ``.unlock()`` when it goes out of scope.

To illustrate synchronisation we are going to implement an application that uses threads that updates a global counter. To illustrate both with and without synchronisation we are going to implement the thread function with and without mutexes.

First we implement a global counter and a mutex:

.. code:: cpp

    #include <vector>
    #include <thread>
    #include <mutex>
    #include <print>

    // Shared resource that multiple threads will modify
    int g_counter = 0;
    std::mutex g_counter_mutex;    

The ``std::mutex`` class is available in the ``<mutex>`` include. Next we implement two versions of the counter update functions. First the naive version that just updates the global variable ``g_counter``.

.. code:: cpp

    void increment_counter_unsafe(int iterations)
    {
        for (auto i = 0; i < iterations; i++)
            g_counter++;
    }

In the safe version of the function we use a lock guard using ``std::lock_guard`` class. When you create the lock guard object it holds the lock of the selected mutex until it goes out of scope. In this function we aquire the lock in the scope of the for-loop just before we update the ``g_counter`` variable. When the loop-block goes out of scope the ``lock`` instance will release the lock and call ``.unlock`` on the mutex object. The safe version of the function then becomes:

.. code:: cpp

    void increment_counter_safe(int iterations)
    {
        for (auto i = 0; i < iterations; i++)
        {
            std::lock_guard<std::mutex> lock(g_counter_mutex);
            g_counter++;
        }
    }    

In out main function we first start 10 threads using the unsafe function. We then print out a comparison of the number of increments we have on the ``g_counter`` variable compared to the expected increments.

.. code:: cpp

    const int num_threads = 10;
    const int iterations_per_thread = 100000;
    
    // Test 1: Without mutex (race condition)
 
    std::print("Test 1: WITHOUT mutex protection");
    g_counter = 0;
    
    {
        std::vector<std::jthread> threads;
        for (int i = 0; i < num_threads; i++)
            threads.emplace_back(increment_counter_unsafe, iterations_per_thread);
    }

    std::println("Expected: {}", num_threads * iterations_per_thread);
    std::println("Actual:   {}", g_counter);
    std::println("Lost updates: {}", num_threads * iterations_per_thread - g_counter);    

The extra brackets around the thread creation loop can look a bit odd, but it make sures that the ``.join()`` methods are called on the ``jthread`` objects and that the threads are completed before continuing.

The safe increment function is called in the same way.

.. code:: cpp

    std::println("Test 2: WITH mutex protection (using lock_guard)");
    g_counter = 0;
    
    {
        std::vector<std::jthread> threads;
        for (int i = 0; i < num_threads; i++)
            threads.emplace_back(increment_counter_safe, iterations_per_thread);
    }
    
    std::println("Expected: {}", num_threads * iterations_per_thread);
    std::println("Actual:   {}", g_counter);
    std::println("Lost updates: {}", num_threads * iterations_per_thread - g_counter);
    
    return 0;

If we run the code we get the following output:

.. code::

    Test 1: WITHOUT mutex protection
    Expected: 1000000
    Actual:   500000
    Lost updates: 500000
    Test 2: WITH mutex protection (using lock_guard)
    Expected: 1000000
    Actual:   1000000
    Lost updates: 0

This example clearly shows that is very important to synchronising access to resources when multiple threads are modifying them. The complete example is shown below.

.. tabs::

    .. tab:: Example

        .. literalinclude:: ../../ch_concurrency/threads3.cpp

    .. tab:: Output

        .. code:: 

            Test 1: WITHOUT mutex protection
            Expected: 1000000
            Actual:   500000
            Lost updates: 500000
            Test 2: WITH mutex protection (using lock_guard)
            Expected: 1000000
            Actual:   1000000
            Lost updates: 0

.. button-link:: https://godbolt.org/z/Moba947ar
    :color: primary
    :outline:
    
    Try example


Practical Parallel Computing
----------------------------

To illustrate the limits of threading, when it works and when it doesn't, we are going to implement 2 similar applications. One that implements the classical SAXPY algorithm and another that is more compute heavy.

Implementing SAXPY using threads and lambda-functions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The SAXPY operation is a very common BLAS operation, which performs the following operation:

.. math::

    \mathbf{y} = \alpha \mathbf{x} + \mathbf{y}

A serial naive version of this operation can be implemented in C++ using the following function:

.. code:: cpp

    void saxpy_serial(double z[], double a, double x[], double y[], long n)
    {
        std::println("Performing SAXPY serially.");

        for (long i = 0; i < n; i++)
            z[i] = a * x[i] + y[i];
    }    

It loops over all elements in ``x`` and ``y`` and computes the elements in the ``z`` array.

In the parallel version we are going to use ``jthreads`` combined with a lamda function for the actual SAXPY operation. Also, we are going to hide all the threading inside the parallel version of the function, so the function will have the same arguments as the serial version.

.. code:: cpp

    void saxpy(double z[], double a, double x[], double y[], long n)

Next we define the number of threads to use and setup our lambda function. Note that we use ``std::min()`` and ``std::thread::hardware_concurrency()`` to determine the number of threads we are going to use. The lambda function is quite simple as it can operate directly on the incoming arrays. The arguments are the ``start`` and ``end`` positions which will be provided for each thread. We can see here that we can reuse our lambda function for multiple threads.

.. code:: cpp

    const auto numThreads = std::min(8u, std::thread::hardware_concurrency());

    std::println("Performing SAXPY with {0} threads.", numThreads);
    
    auto lambda = [z, a, x, y](long start, long end) {
        for (long i = start; i < end; i++)
            z[i] = a * x[i] + y[i];
    };    

In the next step we create a vector of our threads and a loop to compute the range for each thread and create each thread using the ``.emplace_back()`` method of the vector.

.. code:: cpp

    std::vector<std::jthread> threads;
    long chunkSize = n / numThreads;

    std::print("Chunk size = {0}\n", chunkSize);
    
    for (unsigned int i = 0; i < numThreads; i++)
    {
        long start = i * chunkSize;
        long end = (i == numThreads - 1) ? n : (i + 1) * chunkSize;
        threads.emplace_back(lambda, start, end);
    }

But where do we wait on thread completion? As we are implementing this in a function with its own scope we can rely on the ``std::jsthread`` destructor to do an automatic join when the object goes out of scope, which happens at the end of the function.

In the main program we allocate our arrays using unique pointers avoiding ``new`` and ``delete``. We also initalise the arrays to some values.

.. code:: cpp

    const int N = 200000000; // 100 million elements

    std::print("Allocating arrays of size N = {0}...\n", N);
    std::print("Allocated size in MB = {0}\n", (3 * N * sizeof(double)) / (1024.0 * 1024.0));

    auto x = std::make_unique<double[]>(N);
    auto y = std::make_unique<double[]>(N);
    auto z = std::make_unique<double[]>(N);

    for (auto i = 0; i < N; i++)
    {
        x[i] = static_cast<double>(i);
        y[i] = static_cast<double>(i * 2);
    }

We then run our functions and measure time using the functions in the ``std::chrono::high_resolution_clock::now()`` function in the standard library. 

.. code:: cpp

    auto startTimeThreads = std::chrono::high_resolution_clock::now();
    saxpy(z.get(), 3.14, x.get(), y.get(), N);
    auto endTimeThreads = std::chrono::high_resolution_clock::now();

    std::print("Completed SAXPY (threaded) with N = {0} elements.\n", N);

    auto startTimeSerial = std::chrono::high_resolution_clock::now();
    saxpy_serial(z.get(), 3.14, x.get(), y.get(), N);
    auto endTimeSerial = std::chrono::high_resolution_clock::now();

    std::print("Completed SAXPY (serial) with N = {0} elements.\n", N);

    auto timeThreads = std::chrono::duration<double>(endTimeThreads - startTimeThreads).count();
    auto timeSerial = std::chrono::duration<double>(endTimeSerial - startTimeSerial).count();

    std::print("Serial execution time = {0} seconds.\n", timeSerial);
    std::print("Thread execution time = {0} seconds.\n", timeThreads);
    std::print("Speedup = {0}x\n", timeSerial / timeThreads);    

What speedup should we expect from this implementation? Since the SAXPY operation is very simple (just one multiplication and one addition per element), we might initially expect good parallel speedup. However, as we will see, the reality is quite different due to memory bandwidth constraints.

When we run the code we get the following output:

.. code::

    Allocating arrays of size N = 200000000...
    Allocated size in MB = 4577.63671875
    Performing SAXPY with 8 threads.
    Chunk size = 25000000
    Completed SAXPY (threaded) with N = 200000000 elements.
    Performing SAXPY serially.
    Completed SAXPY (serial) with N = 200000000 elements.
    Serial execution time = 0.2421141 seconds.
    Thread execution time = 0.2416036 seconds.
    Speedup = 1.002112965204161x    

But that can't be right? A speedup of only 1.002? Why does this happen? This bad performance is not related compute limitation but on memory bandwidth. The SAXPY operation:

.. code:: cpp

    z[i] = a * x[i] + y[i]

performs only 2 floating point operations (multiplication and addition) but requires:

* 2 memory reads - x[i] and y[i]
* 1 memory write - z[i]

This makes the implementation memory-bound rather than compute-bound. The main problem is that modern CPUs can execute many floating point operations per cycle, but memory bandwidth is shared across all cores. Running 8 threads will try to read/write 24 values simultaneously, saturating the memory subsystem. It doesn't help to add threads as they are competing for the same resources. 

The serial code is as fast because it by itself can saturate the memory subsystem. Also there is a significant overhead of thread creation and synchronisation. Running in serial for these cases also doesn't have any problems with cache coherency and cache line conflicts.

Threading helps when you have more compute heavy codes performing more operations per memory access. Examples can be matrix multiplication, complex calculations and encryption. In the next section we are going to create a more compute heavy application.

The complete example is available here:

.. tabs::

    .. tab:: Code

        .. literalinclude:: ../../ch_concurrency/threads4.cpp

    .. tab:: Output

        .. code:: 

            Test 1: WITHOUT mutex protection
            Expected: 1000000
            Actual:   500000
            Lost updates: 500000
            Test 2: WITH mutex protection (using lock_guard)
            Expected: 1000000
            Actual:   1000000
            Lost updates: 0

.. button-link:: https://godbolt.org/z/TWaEPTfqE
    :color: primary
    :outline:
    
    Try example

A compute heavy example
^^^^^^^^^^^^^^^^^^^^^^^

To illustrate a more compute heavy example we first create a function doing some heave computational operations on an array. The function doesn't perform anything more important than make sure our processor cores are busy. Arguments are the array and start and end positions for the operations.

.. code:: cpp

    // We will use somewhat more functions from the C++ library ;)

    #include <print>
    #include <algorithm>
    #include <atomic>
    #include <chrono>
    #include <cmath>
    #include <memory>
    #include <thread>
    #include <vector>

    void heavyComputation(double *arr, size_t start, size_t end)
    {
        for (size_t i = start; i < end; ++i)
        {
            arr[i] = std::sin(arr[i]) * std::cos(arr[i]) * std::sqrt(std::abs(arr[i]));
            for (int j = 0; j < 100; ++j)
                arr[i] = std::sin(arr[i]);
        }
    }

To make a comparison with a serial version of the code we implement a function, ``processSerial()`` that calls the ``heavyComputation()`` function for the entire array.

.. code:: cpp

    void processSequential(double *data, size_t size)
    {
        heavyComputation(data, 0, size);
    }    

The threaded version of the this function is implemented in ``processParallel()``. This function creates a vector of threads based on the numThreads argument. The threads call the ``heavyComputation()`` function with a specific unique range. Thread synchronisation is automatic as the ``std::jthread`` will automatically join when its destructor is called.

.. code:: cpp

    void processParallel(double *data, size_t size, int numThreads)
    {
        std::vector< std::jthread > threads;
        threads.reserve(numThreads);

        size_t chunkSize = size / numThreads;

        for (int i = 0; i < numThreads; ++i)
        {
            size_t start = i * chunkSize;
            size_t end = (i == numThreads - 1) ? size : (i + 1) * chunkSize;
            threads.emplace_back(heavyComputation, data, start, end);
        }
    }   

In the main program we setup some constants for the test. We use all available threads by assigning ``numThreads`` the value from the function ``std::thread::hardware_concurrency()``. 

.. code:: cpp

    const size_t dataSize = 5000000;
    int numThreads = std::thread::hardware_concurrency();

    std::print("Data size: {0}\n", dataSize);
    std::print("Number of threads: {0}\n", numThreads);

To follow C++ best practice regarding memory allocation we will use unique pointers and ``std::make_unique<>`` to create the memory for the arrays. This will automatically handle cleanup of the array. We create two arrays one for the serial version and one for the parallel version. We also initialise the arrays using an algorithm from the standard library, ``std::generate_n()``, to assign the value 1.0 to all elements. This to make sure our computations are stable.

.. code:: cpp

    std::print("Allocating arrays...\n");

    auto seqData = std::make_unique< double[] >(dataSize);
    auto parData = std::make_unique< double[] >(dataSize);

    std::print("Initialising arrays...\n");

    std::generate_n(seqData.get(), dataSize, []() { return 1.0; });

Now it is time to execute our serial version of our computations and measure the performance. We measure the time and calculate the speedup.

.. code:: cpp

    std::print("Running serially...\n");

    auto start = std::chrono::high_resolution_clock::now();
    processSequential(seqData.get(), dataSize);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration< double > elapsedSerially = end - start;
    std::print("Time for sequential processing: {0} seconds\n", elapsedSerially.count());

    std::print("Running in parallel...\n");

    start = std::chrono::high_resolution_clock::now();
    processParallel(parData.get(), dataSize, numThreads);
    end = std::chrono::high_resolution_clock::now();

    std::chrono::duration< double > elapsedParallel = end - start;

    std::print("Time for parallel processing: {0} seconds\n", elapsedParallel.count());
    std::print("Speedup: {0}\n", elapsedSerially.count() / elapsedParallel.count());

Running this code produce the following output:

.. code::

    Data size: 5000000
    Number of threads: 12
    Allocating arrays...
    Initialising arrays...
    Running serially...
    Time for sequential processing: 3.114036 seconds
    Running in parallel...
    Time for parallel processing: 0.2145049 seconds
    Speedup: 14.517318718593375    

This is a significant improvement from the SAXPY results. Here we are compute-bound and having more threads running on more cores decreases the computational time.

The complete code is available below:

.. tabs::

    .. tab:: Code

        .. literalinclude:: ../../ch_concurrency/threads5.cpp

    .. tab:: Output

        .. code:: 

            Data size: 5000000
            Number of threads: 12
            Allocating arrays...
            Initialising arrays...
            Running serially...
            Time for sequential processing: 3.114036 seconds
            Running in parallel...
            Time for parallel processing: 0.2145049 seconds
            Speedup: 14.517318718593375  

.. button-link:: https://godbolt.org/z/9KzKhM3Y3
    :color: primary
    :outline:
    
    Try example


Advanced Thread Patterns (Atomics)
----------------------------------

There are other ways of implementing synchronisation that has lower performance penalties that using mutexes and lock guards. This can be done using the ``std::atomic<T>`` datatype. This data type uses hardware atomic instructions such as LOCK XADD on x86. This means that the thread never blocks - it either succeeds immediately or retries in a tight loop. There is also no OS involvement which removes any context switches. Usage of atomics is often referred to as lock-free programming and can have large performance benefits.

.. note::

    **When to use atomics vs mutexes:**
    
    * Use ``std::atomic<T>`` for simple operations on single variables (counters, flags, simple accumulation)
    * Use ``std::mutex`` with ``std::lock_guard`` when you need to protect multiple operations or complex data structures
    * Atomics have lower overhead but are limited to simple types and operations
    * For anything more complex than updating a single value, use a mutex

To illustrate how atomics can be used we will modify the heavy computing example to use atomics calculate a sum of the computations from all threads. 

First, the ``heavyComputation()`` function is modified to take an atomic value as input. The thread adds it local sum to this atomic value. Already here you can see how easy it is to use atomics. No more mutex management.

.. code:: cpp

    #include <algorithm>
    #include <atomic>
    #include <chrono>
    #include <cmath>
    #include <memory>
    #include <thread>
    #include <vector>
    #include <print>

    // Function to perform a computationally intensive task
    void heavyComputation(double *arr, size_t start, size_t end, std::atomic<double> &sum)
    {
        double localSum = 0.0;

        for (size_t i = start; i < end; ++i)
        {
            arr[i] = std::sin(arr[i]) * std::cos(arr[i]) * std::sqrt(std::abs(arr[i]));
            for (int j = 0; j < 100; ++j)
            {
                arr[i] = std::sin(arr[i]);
            }
            localSum += arr[i];
        }

        // Atomically add localSum to sum

        sum += localSum;
    }    

As we will reuse the ``heavyComputation()`` function we need a ``processSequentially()`` function to call when timing the results. We are also implement a function for serially initialising the array.

.. code:: cpp

    // Function to process data sequentially
    void processSequential(double *data, size_t size, std::atomic<double> &sum)
    {
        heavyComputation(data, 0, size, sum);
    }    

    void initialiseArray(double *arr, size_t start, size_t end, double value)
    {
        for (size_t i = start; i < end; ++i)
            arr[i] = value;
    }

In this example for the parallel example we will also intialise the array in parallel, so we need a function that does this. This is very similar to our previous examples using a vector of ``std::jthreads``. No atomics needed here as all threads are working on individual parts of the array.

.. code:: cpp

    void initialiseParallel(double *data, size_t size, double value)
    {
        size_t numThreads = std::thread::hardware_concurrency();
        size_t chunkSize = size / numThreads;

        std::vector<std::jthread> threads;
        threads.reserve(numThreads);

        for (size_t i = 0; i < numThreads; ++i)
        {
            size_t start = i * chunkSize;
            size_t end = (i == numThreads - 1) ? size : (i + 1) * chunkSize;
            threads.emplace_back(initialiseArray, data, start, end, value);
        }

        // jthread automatically joins when it goes out of scope - no manual join needed
    }    

The parallel processing is implemented in the ``processParallel()`` function. Also very similar approach as for the initialise function. However we need to use a special function, ``std::ref()`` to pass the atomic variable to the ``.emplace_back()`` method. Otherwise, no magic.

.. code:: cpp

    void processParallel(double *data, size_t size, int numThreads, std::atomic<double> &sum)
    {
        std::vector<std::jthread> threads;
        threads.reserve(numThreads);

        size_t chunkSize = size / numThreads;

        for (int i = 0; i < numThreads; ++i)
        {
            size_t start = i * chunkSize;
            size_t end = (i == numThreads - 1) ? size : (i + 1) * chunkSize;
            threads.emplace_back(heavyComputation, data, start, end, std::ref(sum));
        }
    }

The main function is very similar to our previous examples. First we initialise some constants and arrays. We create two arrays and two atomic sums.

.. code:: cpp

    const size_t dataSize = 800000;
    const int numThreads = std::thread::hardware_concurrency();

    std::printf("Data size: %zu\n", dataSize);
    std::printf("Number of threads: %d\n", numThreads);

    std::print("Allocating arrays...\n");

    auto seqData = std::make_unique<double[]>(dataSize);
    auto parData = std::make_unique<double[]>(dataSize);

    std::atomic<double> seqSum{0.0};
    std::atomic<double> parSum{0.0};   

The serial code the becomes:

.. code:: cpp

    std::print("Initialising arrays serially...\n");

    auto start = std::chrono::high_resolution_clock::now();
    std::generate_n(seqData.get(), dataSize, []() { return 1.0; });
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration< double > elapsedInitSerially = end - start;

    std::printf("Time for serial initialisation: %f seconds\n", elapsedInitSerially.count());

    std::print("Running serially...\n");

    start = std::chrono::high_resolution_clock::now();
    processSequential(seqData.get(), dataSize, seqSum);
    end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsedSerially = end - start;

    std::printf("Time for sequential processing: %f seconds\n", elapsedSerially.count());
    std::printf("Sum: %f\n", seqSum.load());    

To retrieve the value of an atomic you use the ``.load()`` method. The parallel version is very similar.

.. code:: cpp

    std::print("Initialising arrays in parallel...\n");

    start = std::chrono::high_resolution_clock::now();
    initialiseParallel(parData.get(), dataSize, 1.0);
    end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsedInitParallel = end - start;
    
    std::printf("Time for parallel initialisation: %f seconds\n", elapsedInitParallel.count());

    std::print("Running in parallel...\n");

    start = std::chrono::high_resolution_clock::now();
    processParallel(parData.get(), dataSize, numThreads, parSum);
    end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsedParallel = end - start;

    std::printf("Time for parallel processing: %f seconds\n", elapsedParallel.count());
    std::printf("Sum: %f\n", parSum.load());
    std::printf("Speedup: %fx\n", elapsedSerially.count() / elapsedParallel.count());

    return 0;

Running the code produces the following output:

.. code::

    Data size: 800000
    Number of threads: 12
    Allocating arrays...
    Initialising arrays serially...
    Time for serial initialisation: 0.000182 seconds
    Running serially...
    Time for sequential processing: 0.506693 seconds
    Sum: 128779.329092
    Initialising arrays in parallel...
    Time for parallel initialisation: 0.001853 seconds
    Running in parallel...
    Time for parallel processing: 0.074658 seconds
    Sum: 128779.329093
    Speedup: 6.786868x

Here we also see a speedup, but not as significant as for the previous example, but here we also have added the complexity of summarising the data. We can also see that it seems that the parallel version of the intialisation was memory-bound, so we could have used the serial version of the initialisation function to initialise the array.

The complete code is available below:

.. tabs::

    .. tab:: Code

        .. literalinclude:: ../../ch_concurrency/threads6.cpp

    .. tab:: Output

        .. code:: 

            Data size: 800000
            Number of threads: 12
            Allocating arrays...
            Initialising arrays serially...
            Time for serial initialisation: 0.000182 seconds
            Running serially...
            Time for sequential processing: 0.506693 seconds
            Sum: 128779.329092
            Initialising arrays in parallel...
            Time for parallel initialisation: 0.001853 seconds
            Running in parallel...
            Time for parallel processing: 0.074658 seconds
            Sum: 128779.329093
            Speedup: 6.786868x 

.. button-link:: https://godbolt.org/z/bb9dPsbYz
    :color: primary
    :outline:
    
    Try example

Async and Futures
-----------------

There are more ways of implementing concurrency in C++. If your application is more task oriented and doesn't rely on shared data the ``std::async()`` call combined with the ``std::future`` return value can be an effective way of implementing concurrency. The async call is like a non-blocking function call that returns the control back to the main thread. A return value from an async call is something called a future. This is like a placeholder of a future return value. When you want the return value you call the ``.get()`` method of the future. If the async call has finished the method will immediately return the computed return value otherwise it will block until the async call is completed. You can only call the ``.get()`` method once. Calling it multiple times will generate exceptions. It is also possible to check if there is a valid shared state using the method ``.valid()``. It is also possible to wait for a result using the methods ``.wait()`` or ``.wait_for()/wait_until()``. 

To illustrate how async and future can be used we will use our heavy computation example as a base and create functions returning a sum of a complicated computation as a result. The function we will is as follows:

.. code:: cpp

    #include <algorithm>
    #include <chrono>
    #include <cmath>
    #include <future>
    #include <memory>
    #include <print>
    #include <thread>
    #include <vector>

    // Function to perform a computationally intensive task
    double heavyComputation(double *arr, size_t start, size_t end)
    {
        double localSum = 0.0;

        for (size_t i = start; i < end; ++i)
        {
            arr[i] = std::sin(arr[i]) * std::cos(arr[i]) * std::sqrt(std::abs(arr[i]));
            for (int j = 0; j < 1000; ++j)
            {
                arr[i] = std::sin(arr[i]);
            }
            localSum += arr[i];
        }

        return localSum;
    }

There is nothing special with this function. It just returns the local sum. For the asynchronous processing we implement a special function ``processAsync()`` that will do the heavy lifting. As we are going to use the ``std::async()`` function we need to be able to manage the ``std::future`` that the async function will return. We do that by declaring a vector containing a list of future instances.

.. code:: cpp

    double processAsync(double *data, size_t size, int numThreads)
    {
        std::vector< std::future< double > > futures;
        futures.reserve(numThreads);    

Next we will be making a number of calls to the async method in a loop and push back the return futures from the calls. In this case we need to use the ``.push_back()`` method because we need to catch the return values from the async call.

.. code:: cpp

        size_t chunkSize = size / numThreads;

        for (int i = 0; i < numThreads; ++i)
        {
            size_t start = i * chunkSize;
            size_t end = (i == numThreads - 1) ? size : (i + 1) * chunkSize;
            futures.push_back(std::async(std::launch::async, heavyComputation, data, start, end));
        }  

To calculate the sum we can just loop over our future list and call the ``.get()`` method. There is no risk of any synchronisation problems here as the method will block until the task has completed before returning a value. Finally we return the sum.

.. code:: cpp

        double sum = 0.0;

        for (auto &future : futures)
            sum += future.get();

        return sum;
    }

The serial sum just calls the ``heavyComputation()`` method for all elements.

.. code:: cpp

    double processSequential(double *data, size_t size)
    {
        return heavyComputation(data, 0, size);
    }    

Our main program is very similar to our previous examples. We allocate two arrays one for each test using unique pointers. We initialise the arrays using the ``std::generate_n()`` algorithm. We use function from the ``<chrono>`` include from the standard library to measure execution times.

.. code:: cpp

    const size_t dataSize = 5000000;
    const int numThreads = std::thread::hardware_concurrency();

    std::println("Data size: {}", dataSize);
    std::println("Number of threads: {}\n", numThreads);

    std::println("Allocating and initializing arrays...");
    auto seqData = std::make_unique< double[] >(dataSize);
    auto parData = std::make_unique< double[] >(dataSize);

    std::generate_n(seqData.get(), dataSize, []() { return 1.0; });
    std::generate_n(parData.get(), dataSize, []() { return 1.0; });

    std::println("Running sequentially...");
    auto startSeq = std::chrono::high_resolution_clock::now();
    double seqSum = processSequential(seqData.get(), dataSize);
    auto endSeq = std::chrono::high_resolution_clock::now();

    auto elapsedSeq = std::chrono::duration< double >(endSeq - startSeq).count();
    std::println("Sequential - Time: {:.4f} s, Sum: {:.6f}\n", elapsedSeq, seqSum);

    std::println("Running in parallel...");
    auto startPar = std::chrono::high_resolution_clock::now();
    double parSum = processAsync(parData.get(), dataSize, numThreads);
    auto endPar = std::chrono::high_resolution_clock::now();

    auto elapsedPar = std::chrono::duration< double >(endPar - startPar).count();
    std::println("Parallel   - Time: {:.4f} s, Sum: {:.6f}\n", elapsedPar, parSum);

    // Results summary
    std::println("--- Performance Metrics ---");
    std::println("Speedup: {:.2f}x", elapsedSeq / elapsedPar);
    std::println("Efficiency: {:.1f}%", (elapsedSeq / elapsedPar / numThreads) * 100);
    
    double sumDiff = std::abs(seqSum - parSum);
    double relativeError = sumDiff / std::abs(seqSum);
    std::println("Sum difference: {:.2e} (relative error: {:.2e})", sumDiff, relativeError);
    
    // Verify results are reasonably close
    if (relativeError < 1e-10)
        std::println("OK - Results match within acceptable tolerance");
    else
        std::println("Warning: Large difference between sequential and parallel sums");

    return 0;

When running the program we get the following results.

.. code:: cpp

    Data size: 5000000
    Number of threads: 12

    Allocating and initializing arrays...
    Running sequentially...
    Sequential - Time: 30.9081 s, Sum: 271552.176301

    Running in parallel...
    Parallel   - Time: 3.0463 s, Sum: 271552.176326

    --- Performance Metrics ---
    Speedup: 10.15x
    Efficiency: 84.5%
    Sum difference: 2.45e-05 (relative error: 9.03e-11)
    OK - Results match within acceptable tolerance    

This example is compute bound and the tasks are quite self contained only returning a modified array and a sum, which is a perfect example of a suitable use case for the async/future combination in the standard library.


.. tabs::

    .. tab:: Code

        .. literalinclude:: ../../ch_concurrency/async2.cpp

    .. tab:: Output

        .. code:: 

            Data size: 5000000
            Number of threads: 12

            Allocating and initializing arrays...
            Running sequentially...
            Sequential - Time: 30.9081 s, Sum: 271552.176301

            Running in parallel...
            Parallel   - Time: 3.0463 s, Sum: 271552.176326

            --- Performance Metrics ---
            Speedup: 10.15x
            Efficiency: 84.5%
            Sum difference: 2.45e-05 (relative error: 9.03e-11)
            OK - Results match within acceptable tolerance

.. button-link:: https://godbolt.org/z/YOUR_LINK_HERE
    :color: primary
    :outline:
    
    Try example    

Producer-Consumer Pattern with Condition Variables
--------------------------------------------------

One of the most common patterns in concurrent programming is the Producer-Consumer pattern. In this pattern, one or more producer threads generate data and place it in a shared buffer, while one or more consumer threads retrieve and process this data. The challenge is coordinating access to the shared buffer so that:

* Producers wait when the buffer is full
* Consumers wait when the buffer is empty
* Multiple threads don't corrupt the buffer

While we could implement this using just mutexes and busy-waiting (checking repeatedly if a condition is met), this wastes CPU cycles. A better approach is to use ``std::condition_variable``, which allows threads to efficiently wait for a condition to become true.

Understanding Condition Variables
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A ``std::condition_variable`` is a synchronization primitive that allows threads to wait until notified by another thread. It works together with a ``std::mutex`` and typically follows this pattern:

**Waiting thread:**

1. Lock the mutex
2. Check if condition is met
3. If not, call ``.wait()`` which atomically unlocks the mutex and puts the thread to sleep
4. When notified, the thread wakes up and automatically reacquires the lock
5. Recheck the condition (spurious wakeups can occur)
6. Proceed when condition is met

**Notifying thread:**

1. Lock the mutex
2. Modify shared data
3. Unlock the mutex
4. Call ``.notify_one()`` or ``.notify_all()`` to wake waiting threads

The key benefit is that waiting threads sleep instead of consuming CPU cycles in a busy-wait loop.

Implementing the Producer-Consumer Pattern
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Let's implement a thread-safe queue that demonstrates this pattern. First, we'll create a ``SafeQueue`` class that encapsulates the buffer and synchronization:

.. code:: cpp

    template < typename T > class SafeQueue {
    private:
        std::queue< T > m_queue;
        mutable std::mutex m_mutex;
        std::condition_variable m_cond;
        bool m_finished = false;
        size_t m_maxSize;

    public:
        SafeQueue(size_t maxSize = 10) : m_maxSize(maxSize)
        {
        }

        // Producer: Add item to queue (blocks if full)
        void push(T item)
        {
            std::unique_lock< std::mutex > lock(m_mutex);

            // Wait until queue has space
            m_cond.wait(lock, [this]() { return m_queue.size() < m_maxSize || m_finished; });

            if (!m_finished)
            {
                m_queue.push(std::move(item));
                m_cond.notify_one(); // Notify a waiting consumer
            }
        }

        // Consumer: Remove item from queue (blocks if empty)
        std::optional< T > pop()
        {
            std::unique_lock< std::mutex > lock(m_mutex);

            // Wait until queue has data or is finished
            m_cond.wait(lock, [this]() { return !m_queue.empty() || m_finished; });

            if (m_queue.empty())
                return std::nullopt; // No more data

            T item = std::move(m_queue.front());
            m_queue.pop();
            m_cond.notify_one(); // Notify a waiting producer
            return item;
        }

        // Signal that no more items will be produced
        void finish()
        {
            std::unique_lock< std::mutex > lock(m_mutex);
            m_finished = true;
            m_cond.notify_all(); // Wake all waiting threads
        }

        size_t size() const
        {
            std::unique_lock< std::mutex > lock(m_mutex);
            return m_queue.size();
        }
    };

The ``SafeQueue`` uses ``std::unique_lock`` instead of ``std::lock_guard`` because ``std::condition_variable`` needs a lock that can be unlocked and relocked (which happens during ``.wait()``).

Now let's create a complete example with multiple producers and consumers:

.. code:: cpp

    #include <chrono>
    #include <print>
    #include <random>
    #include <thread>
    #include <vector>

    void producer(SafeQueue<int>& queue, int id, int itemCount)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);
        std::uniform_int_distribution<> sleep(10, 100);

        for (int i = 0; i < itemCount; ++i)
        {
            int value = dis(gen);
            queue.push(value);
            std::println("Producer {} produced: {}", id, value);
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep(gen)));
        }
        
        std::println("Producer {} finished", id);
    }

    void consumer(SafeQueue<int>& queue, int id, std::atomic<int>& totalConsumed)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> sleep(50, 150);

        while (true)
        {
            auto item = queue.pop();
            if (!item.has_value())
            {
                std::println("Consumer {} finished (no more items)", id);
                break;
            }
            
            std::println("Consumer {} consumed: {}", id, item.value());
            totalConsumed++;
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep(gen)));
        }
    }

In the main function, we create multiple producers and consumers:

.. code:: cpp

    int main()
    {
        const int numProducers = 3;
        const int numConsumers = 2;
        const int itemsPerProducer = 5;
        
        SafeQueue<int> queue(5);  // Buffer size of 5
        std::atomic<int> totalConsumed{0};
        
        std::println("Starting {} producers and {} consumers", numProducers, numConsumers);
        std::println("Each producer will create {} items\n", itemsPerProducer);
        
        // Start producers
        std::vector<std::jthread> producers;
        for (int i = 0; i < numProducers; ++i)
            producers.emplace_back(producer, std::ref(queue), i, itemsPerProducer);
        
        // Start consumers
        std::vector<std::jthread> consumers;
        for (int i = 0; i < numConsumers; ++i)
            consumers.emplace_back(consumer, std::ref(queue), i, std::ref(totalConsumed));
        
        // Wait for all producers to finish
        producers.clear();  // jthread joins on destruction
        
        std::println("\nAll producers finished. Signaling consumers...");
        queue.finish();
        
        // Wait for all consumers to finish
        consumers.clear();
        
        std::println("\nTotal items produced: {}", numProducers * itemsPerProducer);
        std::println("Total items consumed: {}", totalConsumed.load());
        
        return 0;
    }

When we run this program, we see the interleaved output from multiple producers and consumers, demonstrating concurrent access to the shared queue:

.. code::

    Starting 3 producers and 2 consumers
    Each producer will create 5 items

    Producer 1 produced: 5
    Consumer 0 consumed: 5
    Producer 0 produced: 96
    Producer 2 produced: 66
    Consumer 1 consumed: 66
    Consumer 0 consumed: 96
    Producer 0 produced: 38
    Consumer 1 consumed: 38
    Producer 1 produced: 62
    Producer 2 produced: 99
    Producer 1 produced: 47
    Consumer 0 consumed: 99
    Producer 0 produced: 87
    Producer 2 produced: 58
    Producer 0 produced: 74
    Consumer 1 consumed: 62
    Producer 1 produced: 99
    Consumer 1 consumed: 47
    Producer 0 produced: 44
    Consumer 0 consumed: 87
    Producer 2 produced: 53
    Producer 0 finished
    Consumer 1 consumed: 58
    Producer 1 produced: 94
    Producer 1 finished
    Consumer 0 consumed: 74
    Producer 2 produced: 92
    Consumer 1 consumed: 99
    Consumer 0 consumed: 44
    Producer 2 finished

    All producers finished. Signaling consumers...
    Consumer 1 consumed: 53
    Consumer 1 consumed: 94
    Consumer 0 consumed: 92
    Consumer 0 finished (no more items)
    Consumer 1 finished (no more items)

    Total items produced: 15
    Total items consumed: 15

Key takeaways from this pattern:

* **Efficiency**: Threads sleep when waiting instead of busy-waiting
* **Safety**: The mutex protects shared data from race conditions
* **Coordination**: Condition variables enable efficient thread synchronization
* **Scalability**: Works with any number of producers and consumers
* **Graceful shutdown**: The ``finish()`` method allows clean termination

This pattern is fundamental in many applications: task queues, buffered I/O, event processing, and thread pools.

The complete code is available below:

.. tabs::

    .. tab:: Code

        .. literalinclude:: ../../ch_concurrency/producer_consumer.cpp

    .. tab:: Output

        .. code:: 

            Starting 3 producers and 2 consumers
            Each producer will create 5 items

            Producer 0 produced: 42
            Producer 1 produced: 87
            Producer 2 produced: 23
            Consumer 0 consumed: 42
            Producer 0 produced: 91
            Consumer 1 consumed: 87
            Producer 1 produced: 56
            Producer 2 produced: 34
            Consumer 0 consumed: 23
            Producer 0 produced: 12
            Consumer 1 consumed: 91
            Producer 1 produced: 78
            Producer 2 produced: 67
            Consumer 0 consumed: 56
            Producer 0 produced: 45
            Consumer 1 consumed: 34
            Producer 1 produced: 89
            Producer 2 produced: 90
            Consumer 0 consumed: 12
            Producer 0 produced: 33
            Consumer 1 consumed: 78
            Producer 1 finished
            Producer 2 finished
            Producer 0 finished

            All producers finished. Signaling consumers...
            Consumer 0 consumed: 67
            Consumer 1 consumed: 45
            Consumer 0 consumed: 89
            Consumer 1 consumed: 90
            Consumer 0 consumed: 33
            Consumer 0 finished (no more items)
            Consumer 1 finished (no more items)

            Total items produced: 15
            Total items consumed: 15

.. button-link:: https://godbolt.org/z/YOUR_LINK_HERE
    :color: primary
    :outline:
    
    Try example


Real-World Example: Parallel Stencil Computation
------------------------------------------------

Best Practices and Common Pitfalls
----------------------------------