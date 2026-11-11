CMake and C++
=============

Building C++ applications and libraries for multiple platforms and development environments can be a complicate process. There are multiple different build tools and development tools with different build files and settings. A common tool to solve this problem is CMake. CMake solves this problem by providing a platform neutral way of specifying build requirements and build rules. Instead of relying of complicated build tools with complicated syntax such as Make, the build description is implemented in a full fledged programming language that supports variables, iteration and logic. The language also has an extensive runtime library for interacting with the system and generating build files. 

The process is build around a ``CMakeLists.txt`` file which contains source for the build definition. To run the build generation you use the ``cmake`` command in the source tree, which then builds the required build files. These can be Makefiles, Ninja-files and project files for different development environments.

A first example
---------------

In this example we are going to build the following C++ application:

.. code-block:: cpp

    #include <cmath>
    #include <print>

    int main()
    {
        // Approximate sqrt(2) with Newton's method: x_{n+1} = (x_n + 2/x_n) / 2

        double x = 1.0;

        for (int i = 0; i < 6; ++i)
        {
            x = 0.5 * (x + 2.0 / x);
            std::print("Iteration {}: x = {}\n", i + 1, x);
        }

        std::print("Error compared to std::sqrt(2): {}\n", std::abs(x - std::sqrt(2.0)));
        std::print("Final approximation: x = {}\n", x);

        return 0;
    }


The application just depends on the C++ standard library, so we don't have to specify any additional libraries. 

In the next step we are going to create a ``CMakeLists.txt`` file describing our build. As there are many versions of the CMake tool the first thing we are going to add in this file is a special statement for specifying the mininum version of CMake that the script requires.

.. code-block:: cmake

    cmake_minimum_required(VERSION 3.20)

By keeping the version low we enable the script to be used in more environments where it is not possible to use the latest version. In the next step we add a statement giving the project a name and also specifying which languages we are targeting. We will use the ``project()`` function for this.

.. code-block:: cmake

    project(Hello LANGUAGES CXX) # LANGUAGES is optional

As this example uses modern C++ features we need to set a special variable ``CMAKE_CXX_STANDARD`` that defines the standard we want to use when compiling our example. We will compile against C++23.

.. code-block:: cmake

    set(CMAKE_CXX_STANDARD 23)

In the final part of the script we will define the target and which source files required to build the target. This is done using the ``add_executable()`` function. This function takes the target name (executable name) and a list of source code files required to build the target.

.. code-block:: cmake

    add_executable(hello hello.cpp)

That's it. We are now ready to build our application. The first step is to run ``CMakeLists.txt`` script to configure the build. In this step CMake examines the system and figures out what build tools and compilers are availble. There are some things to consider when calling CMake. By default all build files are generated in the current working directory. This is not optimal as it will pollute the source tree. The recommended way of building your application is to use a build directory, which is specified with the ``-B`` switch. It is also a good idea to indicate where the source directory is located, which is done with the ``-S`` switch. The CMake build command then becomes.

.. code:: text

    C:\...\> cmake -S . -B build 
    -- Building for: Visual Studio 18 2026
    -- Selecting Windows SDK version 10.0.26100.0 to target Windows 10.0.26300.
    -- The CXX compiler identification is MSVC 19.51.36257.0
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Check for working CXX compiler: C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.51.36231/bin/Hostx64/x64/cl.exe - skipped
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Configuring done (4.0s)
    -- Generating done (0.0s)
    -- Build files have been written to: D:/Users/Jonas/Development/cpp_course/ch_cmake/01_single_target/build

The above output is run on a Windows machine, but the output will be similar on Linux or macOS. If we examine the generated build directory we get:

.. code:: text

    2026-11-11  22:26    <DIR>          ALL_BUILD.dir
    2026-11-11  22:26            41 461 ALL_BUILD.vcxproj
    2026-11-11  22:26               318 ALL_BUILD.vcxproj.filters
    2026-11-11  22:26            13 089 CMakeCache.txt
    2026-11-11  22:26    <DIR>          CMakeFiles
    2026-11-11  22:26             2 011 cmake_install.cmake
    2026-11-11  22:26    <DIR>          hello.dir
    2026-11-11  22:26             1 029 Hello.slnx
    2026-11-11  22:26            54 179 hello.vcxproj
    2026-11-11  22:26               640 hello.vcxproj.filters
    2026-11-11  22:26    <DIR>          ZERO_CHECK.dir
    2026-11-11  22:26            41 487 ZERO_CHECK.vcxproj
    2026-11-11  22:26               561 ZERO_CHECK.vcxproj.filters    

This is a standard Visual Studio solution directory, which is the default generator on Windows. Running the same generation on Linux or macOS will produce a make file based build.

We have now configured the build. The next step is to perform the actual build. This is done by using the CMake ``--build`` switch. 

.. code:: text

    C:\...\> cmake --build build
    MSBuild version 18.9.1+a81b43525 for .NET Framework

    1>Checking Build System
    Building Custom Rule D:/Users/Jonas/.../ch_cmake/01_single_target/CMakeLists.txt
    hello.cpp
    hello.vcxproj -> D:\Users\Jonas\...\ch_cmake\01_single_target\build\Debug\hello.exe
    Building Custom Rule D:/Users/Jonas/.../ch_cmake/01_single_target/CMakeLists.txt    

The executable file is placed in the build/Debug directory. Running the program produces the following output:

.. code:: text

    C:\...\> hello.exe
    Iteration 1: x = 1.5
    Iteration 2: x = 1.4166666666666665
    Iteration 3: x = 1.4142156862745097
    Iteration 4: x = 1.4142135623746899
    Iteration 5: x = 1.414213562373095
    Iteration 6: x = 1.414213562373095
    Error compared to std::sqrt(2): 2.220446049250313e-16
    Final approximation: x = 1.414213562373095  

Multiple source files
---------------------

In the previous example we just had a single source code file. This is probarbly the exception. In most cases we have multiple source files perhaps also placed in different directories. In this example we are going to expand on our previous example and rely function placed in separate source files, which also provide header files. Below all files are shown.

.. tabs::

   .. tab:: src/main.cpp

      .. code-block:: cpp

        #include "functions.h"
        #include "integration.h"

        #include <cmath>
        #include <print>

        int main()
        {
            // The integral of x * exp(x) over [0, 1] is exactly 1.
            const double exact = 1.0;

            std::println("{:>8}{:>16}{:>16}", "n", "err trapezoid", "err simpson");

            for (int n = 4; n <= 256; n *= 2)
            {
                double t = trapezoidal(x_exp_x, 0.0, 1.0, n);
                double s = simpson(x_exp_x, 0.0, 1.0, n);
                std::println("{:>8}{:>16.3e}{:>16.3e}", n, std::abs(t - exact), std::abs(s - exact));
            }

            std::println("\nIntegral of damped oscillation on [0, 10]: {}",
                        simpson(damped_oscillation, 0.0, 10.0, 1000));

            return 0;
        }

   .. tab:: src/integration.h

      .. code-block:: cpp

            #pragma once

            #include <functional>

            // Numerical integration of f over [a, b] using n sub-intervals.
            double trapezoidal(const std::function<double(double)>& f, double a, double b, int n);
            double simpson(const std::function<double(double)>& f, double a, double b, int n);

   .. tab:: src/integration.cpp

      .. code-block:: cpp

        #include "integration.h"

        double trapezoidal(const std::function<double(double)>& f, double a, double b, int n)
        {
            const double h = (b - a) / n;
            double sum = 0.5 * (f(a) + f(b));

            for (int i = 1; i < n; ++i)
                sum += f(a + i * h);

            return h * sum;
        }

        double simpson(const std::function<double(double)>& f, double a, double b, int n)
        {
            if (n % 2 != 0)
                ++n; // Simpson's rule needs an even number of intervals

            const double h = (b - a) / n;
            double sum = f(a) + f(b);

            for (int i = 1; i < n; ++i)
                sum += (i % 2 == 0 ? 2.0 : 4.0) * f(a + i * h);

            return h * sum / 3.0;
        }

   .. tab:: src/functions.h

      .. code-block:: cpp

            #pragma once

            // Test functions with known integrals.
            double x_exp_x(double x); // integral over [0, 1] is exactly 1
            double damped_oscillation(double x);
        
   .. tab:: src/functions.cpp

      .. code-block:: cpp

        #include "functions.h"

        #include <cmath>

        double x_exp_x(double x)
        {
            return x * std::exp(x);
        }

        double damped_oscillation(double x)
        {
            return std::exp(-0.1 * x) * std::sin(x);
        }

Just like the previous project we start by specifying the version numbers and the project name.

.. code:: cmake

    cmake_minimum_required(VERSION 3.20)
    project(Integrate VERSION 1.0 LANGUAGES CXX)

We have also added a version tag in the project specification, which can be used when installing or building packages. Next, we add some C++ variables for specifying ths standards.

.. code:: cmake

    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)  # use -std=c++23, not -std=gnu++23

As this example consist of several source files, we add them as a list after the target name in ``add_executable()``.

.. code:: cmake

    add_executable(integrate
        src/main.cpp
        src/integration.cpp
        src/integration.h
        src/functions.cpp
        src/functions.h
    )    

For this example to work we also need to specify where the compiler can find the include files. This is done using the ``target_include_directories()`` function. Using this function we can specify include directories for each target in our project. 

.. code:: cmake

    target_include_directories(integrate PRIVATE src)    

The ``PRIVATE`` attribute tells CMake that the include directory is only for building the example. The ``PUBLIC`` attribute is usually used when building libraries where we want the include files to be installed by the project.

We configure and build using the following commands:

.. code:: text
    
    cmake -S . -B build
    cmake --build build

Multiple targets
----------------

In many project multiple targets are built. This is well supported by CMake as well. By adding multiple ``add_executable()`` statements we can add multiple targets to build. In this example we have 3 targets:

* ``simulate`` consisting of ``simulate.cpp``, ``random_walk.cpp`` and ``random_walk.h``.
* ``analyse`` consisting of ``analyse.cpp``
* ``check_walk`` consisting of ``check_walk.cpp``, ``random_walk.cpp`` and ``random_walk.h``

In this example we are also going to place the built binary files in a ``build/bin``-directory in the source tree. We start with the usual definitions in the ``CMakeLists.txt``.

.. code:: cmake

    cmake_minimum_required(VERSION 3.20)

    project(RandomWalk LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)    

Next we change the output directory of the build.

.. code:: cmake

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

I thing to notice is that paths in the ``CMakeLists.txt`` scripts are always using ``/`` on all platforms. The reason for this is to avoid specific code for each platform. CMake will automatically convert the separator to the correct version depending on the platform CMake is run.

In the next step we specify our executable targets.

.. code:: cmake

    # Program 1: simulate random walks and write final positions to a file.
    add_executable(simulate simulate.cpp random_walk.cpp random_walk.h)

    # Program 2: read the file and compute statistics.
    add_executable(analyse analyse.cpp)

    # Program 3: a quick self-check of the random walk code.
    add_executable(check_walk check_walk.cpp random_walk.cpp random_walk.h)    

We are also going to specify compiler options for each target. Here is it important to note that the compiler options are platform specific and we need to check the platform before applying these. To do this we will be using ``if()``-statements in CMake. The actual compiler flags are specified using the ``target_compile_options()`` function in CMake. We will also be using a loop construct, ``foreach`` to loop over our targets. The following code shows how the compiler options are applied.

.. code:: cmake

    foreach(target IN ITEMS simulate analyse check_walk)
        if(MSVC)
            target_compile_options(${target} PRIVATE /W4)
        else()
            target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
        endif()
    endforeach()    