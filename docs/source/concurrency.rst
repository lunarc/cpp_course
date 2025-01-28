Concurrency
===========

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

            #include <iostream>
            #include <thread>

            std::string to_string(std::thread::id id)
            {
                std::stringstream ss;
                ss << id;
                return ss.str();
            }

            void myfunc()
            {
                std::printf("Thread {} starting.\n", to_string(this_thread::get_id()));
                this_thread::sleep_for(chrono::seconds(1));
                std::printf("Thread {} stopping.\n", to_string(this_thread::get_id()));
            }

            int main()
            {
                jthread t(myfunc);
                t.join();
                std::print("Main thread stopping.\n");
            }

    .. tab:: Output
        
        .. code:: text

            Thread 37968 starting.
            Thread 37968 stopping.
            Main thread stopping.

<a href="https://godbolt.org/z/KjvoT5PcK" class="sd-sphinx-override sd-btn sd-text-wrap sd-btn-outline-primary reference external" style="background-color: transparent;" target="_blank">Try example</a>

In the example above we have defined a function, `myfunc()` that prints its id and waits for a second and the prints that it is stopping. To executed this function on a thread, we create a `std::jthread` object `t` and pass the function to it. The thread will execute immediately when created. As the thread is executed concurrently the main routine can terminate before the thread function terminates, which can lead to undefined behavior. To solve this the thread object has special method, `.join()`, which can be used to wait for the thread to finish.

Syncronization
--------------

Data sharing and race conditions
--------------------------------

Modern concurency features
--------------------------

