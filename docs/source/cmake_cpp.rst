CMake and C++
=============

Building C++ applications and libraries for multiple platforms and development environments can be a complicated process. There are multiple different build tools and development tools with different build files and settings. A common tool to solve this problem is CMake. CMake solves this problem by providing a platform-neutral way of specifying build requirements and build rules. Instead of relying on complicated build tools with complicated syntax such as Make, the build description is implemented in a full-fledged programming language that supports variables, iteration and logic. The language also has an extensive runtime library for interacting with the system and generating build files. 

The process is built around a ``CMakeLists.txt`` file which contains the source for the build definition. To run the build generation you use the ``cmake`` command in the source tree, which then generates the required build files. These can be Makefiles, Ninja files or project files for different development environments.

.. admonition:: In this chapter

    After working through this chapter you will be able to:

    * configure and build a CMake project from the command line on Windows, Linux and macOS,
    * describe a build in terms of *targets* and the properties attached to them,
    * build executables, static libraries and shared libraries and link them together,
    * split a larger project into subdirectories,
    * use third-party libraries with ``find_package()``, vcpkg and FetchContent,
    * add tests to a project and run them with CTest.

.. admonition:: Prerequisites

    * CMake 3.20 or newer. The preset file in the vcpkg section requires CMake 3.25.
    * A C++23 compiler with ``<print>`` support: GCC 14 or newer, Clang 18 or newer, or MSVC from Visual Studio 2022 17.7 or newer.
    * Basic knowledge of compiling and running C++ programs, see :doc:`build_and_run`.

    All examples are available in the ``ch_cmake/`` directory of the course repository. Each subdirectory is a complete, standalone project, and they appear in the same order as in this chapter.

How CMake works
---------------

Before we write our first ``CMakeLists.txt`` it is useful to have a mental model of what CMake actually does. CMake does not compile any code itself. It is a *build system generator*: it reads a description of your project and writes the input files for a native build tool, which then does the actual compiling and linking.

The three steps
~~~~~~~~~~~~~~~

Building a CMake project always goes through three steps:

.. code:: text

    CMakeLists.txt --> configure --> generate --> build --> executables and libraries
                       \______________________/    \___/
                         cmake -S . -B build      cmake --build build

1. **Configure.** CMake runs the ``CMakeLists.txt`` script. It detects the compilers and tools, checks which features they support, looks for dependencies and evaluates options. The results are stored in the file ``CMakeCache.txt`` in the build directory, so later runs are faster.
2. **Generate.** CMake writes the build files for the selected *generator*: Makefiles, Ninja files, or a Visual Studio or Xcode project. Configure and generate are run by the same command, so they are often treated as a single step.
3. **Build.** The native build tool compiles and links the code. You can call the tool directly (``make``, ``ninja`` or Visual Studio), but ``cmake --build build`` works the same way with every generator.

You only need to rerun the configure step yourself when you want to change an option. If you edit a ``CMakeLists.txt`` file, the build step detects this and reruns the configure step automatically.

Source and build directories
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The *source directory* contains your code and the top-level ``CMakeLists.txt``. The *build directory* contains everything that CMake and the build tool generate: the cache, the build files, object files, libraries and executables. Keeping the two apart is called an *out-of-source build* and has several advantages:

* The source tree stays clean, and generated files don't end up in version control. Add ``build/`` to your ``.gitignore``.
* You can start from scratch at any time by deleting the build directory.
* You can have several build directories for the same source, for example one for debug builds and one for release builds, or one per compiler.

This is why we always give both the source directory (``-S``) and the build directory (``-B``) when configuring in this chapter.

Generators
~~~~~~~~~~

CMake picks a default generator for each platform: the newest installed Visual Studio on Windows, and Makefiles on Linux and macOS. You can choose another generator with the ``-G`` switch. Ninja is a popular choice, as it is fast and works the same on all platforms:

.. code:: text

    cmake -S . -B build -G Ninja

The available generators are listed at the end of the output of ``cmake --help``. The generator is fixed once a build directory has been configured. To switch generator, delete the build directory or use a new one. The ``CMakeLists.txt`` file stays the same whatever generator you use.

Targets and properties
~~~~~~~~~~~~~~~~~~~~~~

The central concept in modern CMake is the *target*. A target is either something that should be built, such as an executable (``add_executable()``) or a library (``add_library()``), or something that already exists, such as a library found on the system with ``find_package()``.

Each target has *properties*: its source files, include directories, compiler options, the required C++ standard, the libraries it links against and so on. Most commands in this chapter set properties on a target, and you can recognise them by their ``target_`` prefix:

.. code:: cmake

    add_executable(hello hello.cpp)                     # create a target
    target_compile_features(hello PRIVATE cxx_std_23)   # set a property on it
    target_link_libraries(hello PRIVATE mylib)          # make it depend on another target

When one target links against another, CMake can pass properties on automatically. A program that links against a library then also gets, for example, the include directories of the library. The keywords ``PRIVATE``, ``PUBLIC`` and ``INTERFACE`` control which properties are passed on. We will see how they work in the sections on libraries.

Some settings can also be made for the whole project with variables such as ``CMAKE_CXX_STANDARD``, which provide default values for all targets. This is convenient in small projects, but the ``target_`` commands make it clear which target needs what. A good habit is to think of a ``CMakeLists.txt`` as a list of targets and the relationships between them, not as a list of compiler flags.

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

In the next step we are going to create a ``CMakeLists.txt`` file describing our build. As there are many versions of the CMake tool, the first thing we are going to add in this file is a special statement for specifying the minimum version of CMake that the script requires.

.. code-block:: cmake

    cmake_minimum_required(VERSION 3.20)

By keeping the version low we enable the script to be used in more environments where it is not possible to use the latest version. In the next step we add a statement giving the project a name and also specifying which languages we are targeting. We will use the ``project()`` function for this.

.. code-block:: cmake

    project(Hello LANGUAGES CXX) # LANGUAGES is optional

As this example uses modern C++ features, we need to set a special variable ``CMAKE_CXX_STANDARD`` that defines the standard we want to use when compiling our example. We will compile against C++23.

.. code-block:: cmake

    set(CMAKE_CXX_STANDARD 23)

In the final part of the script we will define the target and which source files are required to build the target. This is done using the ``add_executable()`` function. This function takes the target name (executable name) and a list of source code files required to build the target.

.. code-block:: cmake

    add_executable(hello hello.cpp)

That's it. We are now ready to build our application. The first step is to run the ``CMakeLists.txt`` script to configure the build. In this step CMake examines the system and figures out what build tools and compilers are available. There are some things to consider when calling CMake. By default, all build files are generated in the current working directory. This is not optimal as it will pollute the source tree. The recommended way of building your application is to use a build directory, which is specified with the ``-B`` switch. It is also a good idea to indicate where the source directory is located, which is done with the ``-S`` switch. The CMake build command then becomes:

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

The above output is from a Windows machine, but the output will be similar on Linux or macOS. If we examine the generated build directory we get:

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

This is a standard Visual Studio solution directory, which is the default generator on Windows. Running the same generation on Linux or macOS will produce a Makefile-based build.

We have now configured the build. The next step is to perform the actual build. This is done by using the CMake ``--build`` switch. 

.. code:: text

    C:\...\> cmake --build build
    MSBuild version 18.9.1+a81b43525 for .NET Framework

    1>Checking Build System
    Building Custom Rule D:/Users/Jonas/.../ch_cmake/01_single_target/CMakeLists.txt
    hello.cpp
    hello.vcxproj -> D:\Users\Jonas\...\ch_cmake\01_single_target\build\Debug\hello.exe
    Building Custom Rule D:/Users/Jonas/.../ch_cmake/01_single_target/CMakeLists.txt    

The executable file is placed in the ``build/Debug`` directory. Running the program produces the following output:

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

.. dropdown:: Complete example: ch_cmake/01_single_target
    :icon: code

    .. literalinclude:: ../../ch_cmake/01_single_target/CMakeLists.txt
        :language: cmake
        :caption: CMakeLists.txt

    .. literalinclude:: ../../ch_cmake/01_single_target/hello.cpp
        :language: cpp
        :caption: hello.cpp

.. admonition:: Key points

    * A minimal project needs ``cmake_minimum_required()``, ``project()`` and at least one target.
    * ``add_executable()`` creates an executable target from a list of source files.
    * Configure with ``cmake -S . -B build`` and build with ``cmake --build build``.
    * Where the executable ends up depends on the generator: ``build/`` for Makefiles and Ninja, ``build/Debug/`` for Visual Studio.

.. admonition:: Exercise
    :class: tip

    1. Build ``ch_cmake/01_single_target``, find the executable and run it.
    2. Change the number of iterations in ``hello.cpp`` and run ``cmake --build build`` again. Notice that you don't have to rerun the configure step.
    3. Configure a second build directory with ``cmake -S . -B build-ninja -G Ninja`` (if Ninja is installed) and compare its contents with the first one.

Multiple source files
---------------------

In the previous example we just had a single source code file. This is probably the exception. In most cases we have multiple source files perhaps also placed in different directories. In this example we are going to expand on our previous example and rely on functions placed in separate source files, which also provide header files. All files are shown below.

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

We have also added a version tag in the project specification, which can be used when installing or building packages. Next, we add some variables for specifying the C++ standard.

.. code:: cmake

    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)  # use -std=c++23, not -std=gnu++23

As this example consists of several source files, we add them as a list after the target name in ``add_executable()``.

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

.. dropdown:: Complete example: ch_cmake/02_multiple_sources
    :icon: code

    .. literalinclude:: ../../ch_cmake/02_multiple_sources/CMakeLists.txt
        :language: cmake
        :caption: CMakeLists.txt

    .. literalinclude:: ../../ch_cmake/02_multiple_sources/src/functions.h
        :language: cpp
        :caption: src/functions.h

    .. literalinclude:: ../../ch_cmake/02_multiple_sources/src/integration.h
        :language: cpp
        :caption: src/integration.h

    .. literalinclude:: ../../ch_cmake/02_multiple_sources/src/functions.cpp
        :language: cpp
        :caption: src/functions.cpp

    .. literalinclude:: ../../ch_cmake/02_multiple_sources/src/integration.cpp
        :language: cpp
        :caption: src/integration.cpp

    .. literalinclude:: ../../ch_cmake/02_multiple_sources/src/main.cpp
        :language: cpp
        :caption: src/main.cpp

.. admonition:: Key points

    * List all source files of a target in ``add_executable()``. Header files are listed as well, so that they show up in IDEs.
    * ``target_include_directories()`` tells the compiler where to find header files for a specific target.
    * ``CMAKE_CXX_STANDARD`` sets the C++ standard for all targets in the project.

.. admonition:: Exercise
    :class: tip

    1. In ``ch_cmake/02_multiple_sources``, remove ``src/functions.cpp`` from ``add_executable()`` and build. Read the error message: does it come from the compiler or the linker?
    2. Restore the file, then add a new test function with a known integral to ``functions.h`` and ``functions.cpp`` and integrate it in ``main.cpp``.

Multiple targets
----------------

In many projects multiple targets are built. This is well supported by CMake as well. By adding multiple ``add_executable()`` statements we can add multiple targets to build. In this example we have 3 targets:

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

One thing to notice is that paths in the ``CMakeLists.txt`` scripts always use ``/`` on all platforms. The reason for this is to avoid specific code for each platform. CMake will automatically convert the separator to the correct version depending on the platform CMake is run on.

In the next step we specify our executable targets.

.. code:: cmake

    # Program 1: simulate random walks and write final positions to a file.
    add_executable(simulate simulate.cpp random_walk.cpp random_walk.h)

    # Program 2: read the file and compute statistics.
    add_executable(analyse analyse.cpp)

    # Program 3: a quick self-check of the random walk code.
    add_executable(check_walk check_walk.cpp random_walk.cpp random_walk.h)    

We are also going to specify compiler options for each target. Here it is important to note that the compiler options are platform specific and we need to check the platform before applying these. To do this we will be using ``if()``-statements in CMake. The actual compiler flags are specified using the ``target_compile_options()`` function in CMake. We will also be using a loop construct, ``foreach()``, to loop over our targets. The following code shows how the compiler options are applied.

.. code:: cmake

    foreach(target IN ITEMS simulate analyse check_walk)
        if(MSVC)
            target_compile_options(${target} PRIVATE /W4)
        else()
            target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
        endif()
    endforeach()    

Let's now build the project using the commands we discussed earlier. The binaries will be placed in the ``build/bin`` directory as specified. This time we are running the commands on an Ubuntu machine.

.. code:: text

    $ cmake -S . -B build
    -- The CXX compiler identification is GNU 15.3.0
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Check for working CXX compiler: /usr/bin/c++ - skipped
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Configuring done (0.1s)
    -- Generating done (0.0s)
    -- Build files have been written to: /home/.../cpp_course/ch_cmake/03_multiple_targets/build
    
    $ cmake --build build
    [ 12%] Building CXX object CMakeFiles/simulate.dir/simulate.cpp.o
    [ 25%] Building CXX object CMakeFiles/simulate.dir/random_walk.cpp.o
    [ 37%] Linking CXX executable bin/simulate
    [ 37%] Built target simulate
    [ 50%] Building CXX object CMakeFiles/analyse.dir/analyse.cpp.o
    [ 62%] Linking CXX executable bin/analyse
    [ 62%] Built target analyse
    [ 75%] Building CXX object CMakeFiles/check_walk.dir/check_walk.cpp.o
    [ 87%] Building CXX object CMakeFiles/check_walk.dir/random_walk.cpp.o
    [100%] Linking CXX executable bin/check_walk
    [100%] Built target check_walk


After building, you can run the executables from the ``build/bin`` directory:

.. code:: text

    $ ./build/bin/simulate 
    Wrote 10000 positions to positions.txt
    $ ./build/bin/analyse 
    Samples  : 10000
    Mean     : 0.1046
    Std. dev.: 10.0587  (theory for 100 steps: 10)
    $ ./build/bin/check_walk 
    OK

With this example we have shown that you can use the same ``CMakeLists.txt`` for multiple platforms without any changes. 

.. dropdown:: Complete example: ch_cmake/03_multiple_targets
    :icon: code

    .. literalinclude:: ../../ch_cmake/03_multiple_targets/CMakeLists.txt
        :language: cmake
        :caption: CMakeLists.txt

    .. literalinclude:: ../../ch_cmake/03_multiple_targets/random_walk.h
        :language: cpp
        :caption: random_walk.h

    .. literalinclude:: ../../ch_cmake/03_multiple_targets/analyse.cpp
        :language: cpp
        :caption: analyse.cpp

    .. literalinclude:: ../../ch_cmake/03_multiple_targets/check_walk.cpp
        :language: cpp
        :caption: check_walk.cpp

    .. literalinclude:: ../../ch_cmake/03_multiple_targets/random_walk.cpp
        :language: cpp
        :caption: random_walk.cpp

    .. literalinclude:: ../../ch_cmake/03_multiple_targets/simulate.cpp
        :language: cpp
        :caption: simulate.cpp

.. admonition:: Key points

    * A project can contain any number of targets, each defined with its own ``add_executable()``.
    * ``CMAKE_RUNTIME_OUTPUT_DIRECTORY`` collects all executables in one directory.
    * Compiler options are platform specific. Use ``if(MSVC)`` to select the right ones, and ``target_compile_options()`` to set them.
    * Paths in ``CMakeLists.txt`` always use ``/``, on all platforms.

.. admonition:: Exercise
    :class: tip

    1. In ``ch_cmake/03_multiple_targets``, build only one of the programs with ``cmake --build build --target analyse``.
    2. Introduce an unused variable in ``analyse.cpp`` and check that the compiler now gives a warning. Then make warnings into errors by adding ``-Werror`` (or ``/WX`` for MSVC) to the compiler options.

Static libraries
----------------

Another common task in software development is to build libraries that can be used by other applications. CMake also supports building libraries using the ``add_library()`` function. The function works in a similar way to ``add_executable()`` but instead builds a library.

In this example we are going to build a single library, ``stats``, that is going to be used by two executable targets: ``describe`` and ``fit_line``. The source code is shown below:

.. tabs::

   .. tab:: apps/describe.cpp

      .. code-block:: cpp

        #include <stats/descriptive.h>

        #include <print>
        #include <vector>

        int main()
        {
            // Measured yield stress [MPa] from a series of tensile tests.
            std::vector<double> yield = {251.3, 248.9, 255.1, 249.7, 252.4, 247.2, 253.8, 250.6};

            std::println("Mean   : {:.2f} MPa", stats::mean(yield));
            std::println("Median : {:.2f} MPa", stats::median(yield));
            std::println("Std dev: {:.2f} MPa", stats::stddev(yield));

            return 0;
        }

   .. tab:: apps/fit_line.cpp

      .. code-block:: cpp

        #include <stats/regression.h>

        #include <print>
        #include <vector>

        int main()
        {
            // Strain [-] and stress [MPa] in the elastic region of a steel specimen.
            std::vector<double> strain = {0.0000, 0.0002, 0.0004, 0.0006, 0.0008, 0.0010};
            std::vector<double> stress = {0.0, 41.8, 83.1, 124.9, 165.7, 208.2};

            auto fit = stats::linear_fit(strain, stress);

            std::println("Young's modulus E = {:.1f} GPa", fit.slope / 1000.0);
            std::println("Intercept         = {:.3f} MPa", fit.intercept);
            std::println("R^2               = {:.6f}", fit.r2);

            return 0;
        }

   .. tab:: stats/include/descriptive.h

      .. code-block:: cpp

        #pragma once

        #include <span>

        namespace stats {

        double mean(std::span<const double> x);
        double variance(std::span<const double> x); // sample variance (n - 1)
        double stddev(std::span<const double> x);
        double median(std::span<const double> x);

        } // namespace stats

   .. tab:: stats/include/regression.h

      .. code-block:: cpp

        #pragma once

        #include <span>

        namespace stats {

        struct LinearFit
        {
            double slope;
            double intercept;
            double r2; // coefficient of determination
        };

        // Least squares fit of y = slope * x + intercept.
        LinearFit linear_fit(std::span<const double> x, std::span<const double> y);

        } // namespace stats

   .. tab:: stats/src/descriptive.cpp

      .. code-block:: cpp

        #include <stats/descriptive.h>

        #include <algorithm>
        #include <cmath>
        #include <numeric>
        #include <vector>

        namespace stats {

        double mean(std::span<const double> x)
        {
            return std::accumulate(x.begin(), x.end(), 0.0) / static_cast<double>(x.size());
        }

        double variance(std::span<const double> x)
        {
            const double m = mean(x);
            double sum = 0.0;
            for (double v : x)
                sum += (v - m) * (v - m);
            return sum / static_cast<double>(x.size() - 1);
        }

        double stddev(std::span<const double> x)
        {
            return std::sqrt(variance(x));
        }

        double median(std::span<const double> x)
        {
            std::vector<double> sorted(x.begin(), x.end());
            std::sort(sorted.begin(), sorted.end());

            const auto n = sorted.size();
            return n % 2 == 1 ? sorted[n / 2] : 0.5 * (sorted[n / 2 - 1] + sorted[n / 2]);
        }

        } // namespace stats

   .. tab:: stats/src/regression.cpp

      .. code-block:: cpp

        #include <stats/descriptive.h>
        #include <stats/regression.h>

        namespace stats {

        LinearFit linear_fit(std::span<const double> x, std::span<const double> y)
        {
            const double mx = mean(x);
            const double my = mean(y);

            double sxy = 0.0, sxx = 0.0, syy = 0.0;
            for (std::size_t i = 0; i < x.size(); ++i)
            {
                sxy += (x[i] - mx) * (y[i] - my);
                sxx += (x[i] - mx) * (x[i] - mx);
                syy += (y[i] - my) * (y[i] - my);
            }

            LinearFit fit;
            fit.slope = sxy / sxx;
            fit.intercept = my - fit.slope * mx;
            fit.r2 = (sxy * sxy) / (sxx * syy);
            return fit;
        }

        } // namespace stats

To create our ``CMakeLists.txt`` we start with the standard statements defining version, project name and where to place our binaries. 

.. code:: cmake

    cmake_minimum_required(VERSION 3.20)

    project(StatsDemo VERSION 1.0 LANGUAGES CXX)   

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 

Next, we add our library definition using the ``add_library()`` function.

.. code:: cmake

    add_library(stats STATIC
        stats/src/descriptive.cpp
        stats/src/regression.cpp
        stats/include/stats/descriptive.h
        stats/include/stats/regression.h
    )    

The ``STATIC`` attribute indicates that it is a static library, which means it is linked directly with the binary and not loaded dynamically at runtime. 

We also need to specify how the users of the library can include the library. This is done by using the ``target_include_directories()`` command. In this case we will use the ``PUBLIC`` directive to indicate that the include files should be added to the system path and they will also be added when the library is installed.

.. code:: cmake

    target_include_directories(stats PUBLIC stats/include)

As we are using C++23, we need to indicate that this library needs this standard, so any target is also compiled using C++23. We can indicate this by using the ``target_compile_features()`` function.

.. code:: cmake

    target_compile_features(stats PUBLIC cxx_std_23)

We are now ready to add our executable targets. 

.. code:: cmake

    add_executable(describe apps/describe.cpp)
    add_executable(fit_line apps/fit_line.cpp)

The final step in this example is to make sure that our targets link with our static library, ``stats``. This is done using the ``target_link_libraries()`` function.

.. code:: cmake

    target_link_libraries(describe PRIVATE stats)
    target_link_libraries(fit_line PRIVATE stats)

These functions will add the required include and library directories when compiling. We can now compile the library just like before.

.. code:: text

    $ cmake -S . -B build
    -- The CXX compiler identification is GNU 15.3.0
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Check for working CXX compiler: /usr/bin/c++ - skipped
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Configuring done (0.1s)
    -- Generating done (0.0s)
    -- Build files have been written to: /home/lindemann/Development/cpp_course/ch_cmake/04_static_library/build

    $ cmake --build build
    [ 14%] Building CXX object CMakeFiles/stats.dir/stats/src/descriptive.cpp.o
    [ 28%] Building CXX object CMakeFiles/stats.dir/stats/src/regression.cpp.o
    [ 42%] Linking CXX static library libstats.a
    [ 42%] Built target stats
    [ 57%] Building CXX object CMakeFiles/describe.dir/apps/describe.cpp.o
    [ 71%] Linking CXX executable bin/describe
    [ 71%] Built target describe
    [ 85%] Building CXX object CMakeFiles/fit_line.dir/apps/fit_line.cpp.o
    [100%] Linking CXX executable bin/fit_line
    [100%] Built target fit_line

We see here that it builds the library ``libstats.a``. Running this on a Windows machine would produce a library called ``stats.lib`` instead.

.. dropdown:: Complete example: ch_cmake/04_static_library
    :icon: code

    .. literalinclude:: ../../ch_cmake/04_static_library/CMakeLists.txt
        :language: cmake
        :caption: CMakeLists.txt

    .. literalinclude:: ../../ch_cmake/04_static_library/stats/include/stats/descriptive.h
        :language: cpp
        :caption: stats/include/stats/descriptive.h

    .. literalinclude:: ../../ch_cmake/04_static_library/stats/include/stats/regression.h
        :language: cpp
        :caption: stats/include/stats/regression.h

    .. literalinclude:: ../../ch_cmake/04_static_library/apps/describe.cpp
        :language: cpp
        :caption: apps/describe.cpp

    .. literalinclude:: ../../ch_cmake/04_static_library/apps/fit_line.cpp
        :language: cpp
        :caption: apps/fit_line.cpp

    .. literalinclude:: ../../ch_cmake/04_static_library/stats/src/descriptive.cpp
        :language: cpp
        :caption: stats/src/descriptive.cpp

    .. literalinclude:: ../../ch_cmake/04_static_library/stats/src/regression.cpp
        :language: cpp
        :caption: stats/src/regression.cpp

.. admonition:: Key points

    * ``add_library(name STATIC ...)`` builds a static library that is linked into each executable using it.
    * ``target_link_libraries()`` links a target with a library. Include directories and compile features marked ``PUBLIC`` on the library are passed on to the targets linking with it.
    * ``target_compile_features()`` states which C++ standard a target needs.

.. admonition:: Exercise
    :class: tip

    1. In ``ch_cmake/04_static_library``, change ``PUBLIC`` to ``PRIVATE`` in the ``target_include_directories()`` call for ``stats``. Which targets fail to build now, and why?
    2. Add a new function, for example the median, to the ``stats`` library and use it in ``describe.cpp``. Which ``CMakeLists.txt`` changes are needed?

Shared library
--------------

A shared library is loaded when the program runs instead of being included in the built executable. On Windows a shared library is what is known as a ``.dll``-file. On Linux shared libraries are identified with the extension ``.so`` and on macOS they have the extension ``.dylib``. 

Shared libraries differ slightly between the platforms. On Windows, functions in a DLL need to be explicitly exported from a DLL. On Windows the library must be in the same directory as the executable or available in the ``PATH``. On Linux the location of the library must be added to the environment variable ``LD_LIBRARY_PATH`` unless they are installed in the system directories.

Shared libraries are defined in mostly the same way as for static libraries. It is also possible to add an option for which type of library to build in the ``CMakeLists.txt`` file. For the Windows platform CMake can also generate a special header file for the exported functions.

In this example we will build an ODE solver that is loaded from a shared library, ``ode``. We have the following source files:

.. tabs::

   .. tab:: ode/include/solvers.h

      .. code-block:: cpp

            #pragma once

            #include <ode_export.h> // generated by CMake, defines ODE_EXPORT

            #include <functional>
            #include <vector>

            namespace ode {

            using State = std::vector<double>;

            // Right-hand side of the system dy/dt = f(t, y).
            using RHS = std::function<State(double t, const State& y)>;

            // Advance the solution one step of size h.
            ODE_EXPORT State euler_step(const RHS& f, double t, const State& y, double h);
            ODE_EXPORT State rk4_step(const RHS& f, double t, const State& y, double h);

            } // namespace ode

   .. tab:: ode/src/solvers.cpp

      .. code-block:: cpp

            #include <ode/solvers.h>

            namespace ode {

            namespace {

            // y + a * k, element by element. Lives in an anonymous namespace and is
            // therefore not visible outside the library.
            State axpy(const State& y, double a, const State& k)
            {
                State result(y.size());
                for (std::size_t i = 0; i < y.size(); ++i)
                    result[i] = y[i] + a * k[i];
                return result;
            }

            } // namespace

            State euler_step(const RHS& f, double t, const State& y, double h)
            {
                return axpy(y, h, f(t, y));
            }

            State rk4_step(const RHS& f, double t, const State& y, double h)
            {
                const State k1 = f(t, y);
                const State k2 = f(t + h / 2, axpy(y, h / 2, k1));
                const State k3 = f(t + h / 2, axpy(y, h / 2, k2));
                const State k4 = f(t + h, axpy(y, h, k3));

                State result(y.size());
                for (std::size_t i = 0; i < y.size(); ++i)
                    result[i] = y[i] + h / 6.0 * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
                return result;
            }

            } // namespace ode

   .. tab:: apps/oscillator.cpp

      .. code-block:: cpp

            #include <ode/solvers.h>

            #include <cmath>
            #include <print>

            int main()
            {
                // Undamped harmonic oscillator x'' = -omega^2 x written as a system
                // y = [x, v], y' = [v, -omega^2 x].
                const double omega = 2.0;
                ode::RHS f = [omega](double, const ode::State& y) {
                    return ode::State{y[1], -omega * omega * y[0]};
                };

                const double h = 0.05;
                const int n_steps = 200; // integrate to t = 10

                ode::State y_euler = {1.0, 0.0};
                ode::State y_rk4 = {1.0, 0.0};

                double t = 0.0;
                for (int i = 0; i < n_steps; ++i)
                {
                    y_euler = ode::euler_step(f, t, y_euler, h);
                    y_rk4 = ode::rk4_step(f, t, y_rk4, h);
                    t += h;
                }

                const double exact = std::cos(omega * t);

                std::println("x({:.1f}) exact : {:9.6f}", t, exact);
                std::println("x({:.1f}) Euler : {:9.6f}  error {:.2e}", t, y_euler[0], std::abs(y_euler[0] - exact));
                std::println("x({:.1f}) RK4   : {:9.6f}  error {:.2e}", t, y_rk4[0], std::abs(y_rk4[0] - exact));

                return 0;
            }

To implement the ``CMakeLists.txt`` we add our standard project and version information.

.. code:: cmake

    cmake_minimum_required(VERSION 3.20)

    project(OdeDemo VERSION 1.0 LANGUAGES CXX)

Next we set a special CMake variable, ``BUILD_SHARED_LIBS``, that controls how libraries should be built. There is no need to specify any special directives when defining the library targets if this option is set to ``ON``.

.. code:: cmake

    option(BUILD_SHARED_LIBS "Build libraries as shared libraries" ON)

To keep track of all the built files we set the output directories explicitly.

.. code:: cmake

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

Next we define our library and compile features.

.. code:: cmake

    add_library(ode
        ode/src/solvers.cpp
        ode/include/ode/solvers.h
    )

    target_include_directories(ode PUBLIC
        ode/include
        ${CMAKE_CURRENT_BINARY_DIR}   # location of the generated ode_export.h
    )

    target_compile_features(ode PUBLIC cxx_std_23)  

To make sure only functions marked with ``ODE_EXPORT`` are visible to users we set special properties of the target using ``set_target_properties``.

.. code:: cmake

    set_target_properties(ode PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
        VERSION ${PROJECT_VERSION}            # libode.so.1.0
        SOVERSION ${PROJECT_VERSION_MAJOR}    # libode.so.1
    )

Next we need to generate the ``build/ode_export.h`` file, which is done using the following functions.

.. code:: cmake

    include(GenerateExportHeader)
    generate_export_header(ode)

Finally we add our executable target and link it with our new shared library.

.. code:: cmake

    add_executable(oscillator apps/oscillator.cpp)
    target_link_libraries(oscillator PRIVATE ode)

Let's build our library.

.. code:: text

    $ cmake -S . -B build
    -- The CXX compiler identification is GNU 15.3.0
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Check for working CXX compiler: /usr/bin/c++ - skipped
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Performing Test COMPILER_HAS_HIDDEN_VISIBILITY
    -- Performing Test COMPILER_HAS_HIDDEN_VISIBILITY - Success
    -- Performing Test COMPILER_HAS_HIDDEN_INLINE_VISIBILITY
    -- Performing Test COMPILER_HAS_HIDDEN_INLINE_VISIBILITY - Success
    -- Performing Test COMPILER_HAS_DEPRECATED_ATTR
    -- Performing Test COMPILER_HAS_DEPRECATED_ATTR - Success
    -- Configuring done (0.3s)
    -- Generating done (0.0s)
    -- Build files have been written to: /home/.../cpp_course/ch_cmake/05_shared_library/build
    
    $ cmake --build build
    [ 25%] Building CXX object CMakeFiles/ode.dir/ode/src/solvers.cpp.o
    [ 50%] Linking CXX shared library lib/libode.so
    [ 50%] Built target ode
    [ 75%] Building CXX object CMakeFiles/oscillator.dir/apps/oscillator.cpp.o
    [100%] Linking CXX executable bin/oscillator
    [100%] Built target oscillator

We can see here that the build generated the shared library ``lib/libode.so`` and the executable ``bin/oscillator``. Running the executable gives us.

.. code:: text

    $ ./oscillator 
    x(10.0) exact :  0.408082
    x(10.0) Euler :  1.264886  error 8.57e-01
    x(10.0) RK4   :  0.408097  error 1.46e-05

So how can we see that our executable uses our shared library? In Linux there is a tool, ``ldd``, for querying which libraries will be loaded by the executable. Running this tool on our ``oscillator`` binary produces the following output.

.. code:: text
    
    $ ldd oscillator 
        linux-vdso.so.1 (0x00007449faa32000)
        libode.so.1 => /home/.../build/lib/libode.so.1 (0x00007449fa9e3000)
        libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007449fa600000)
        libm.so.6 => /usr/lib/x86_64-linux-gnu/libm.so.6 (0x00007449fa4d5000)
        libgcc_s.so.1 => /usr/lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007449fa9b5000)
        libc.so.6 => /usr/lib/x86_64-linux-gnu/libc.so.6 (0x00007449fa200000)
        /lib64/ld-linux-x86-64.so.2 (0x00007449faa35000)

We can clearly see that the executable links against ``libode.so.1``, which it should. ``ldd`` is a good tool for debugging dynamic linking issues.

Our build also generated a special header file, ``ode_export.h``, to handle the exported functions, which is located in the build directory. The header contains the definition of ``ODE_EXPORT`` depending on the platform and whether we are building or using the library. If we look in the header file of our library we can see how it is used.

.. code:: cpp

    ODE_EXPORT State euler_step(const RHS& f, double t, const State& y, double h);
    ODE_EXPORT State rk4_step(const RHS& f, double t, const State& y, double h); 

.. dropdown:: Complete example: ch_cmake/05_shared_library
    :icon: code

    .. literalinclude:: ../../ch_cmake/05_shared_library/CMakeLists.txt
        :language: cmake
        :caption: CMakeLists.txt

    .. literalinclude:: ../../ch_cmake/05_shared_library/ode/include/ode/solvers.h
        :language: cpp
        :caption: ode/include/ode/solvers.h

    .. literalinclude:: ../../ch_cmake/05_shared_library/apps/oscillator.cpp
        :language: cpp
        :caption: apps/oscillator.cpp

    .. literalinclude:: ../../ch_cmake/05_shared_library/ode/src/solvers.cpp
        :language: cpp
        :caption: ode/src/solvers.cpp

.. admonition:: Key points

    * A shared library is loaded at runtime. Executables using it must be able to find it, on Windows typically in the same directory.
    * ``BUILD_SHARED_LIBS`` decides whether ``add_library()`` without ``STATIC`` or ``SHARED`` builds a static or a shared library.
    * ``generate_export_header()`` creates the ``ODE_EXPORT`` macro that marks which functions are exported from the library.
    * On Linux, ``ldd`` shows which shared libraries an executable will load.

.. admonition:: Exercise
    :class: tip

    1. In ``ch_cmake/05_shared_library``, configure a new build directory with ``-DBUILD_SHARED_LIBS=OFF``. Compare the build output and, on Linux, the output of ``ldd`` with the shared build.
    2. Remove ``ODE_EXPORT`` from ``rk4_step`` in ``solvers.h`` and build again. What error do you get, and why?

Project structure
-----------------

When your project grows it can be complicated to maintain all parts using a single ``CMakeLists.txt`` file. To handle this you can divide up CMake functionality into multiple ``CMakeLists.txt`` files located in subdirectories in your project. Each of these will operate relative to the subdirectory it is running in. You add a subdirectory with a ``CMakeLists.txt`` using the ``add_subdirectory()`` function in CMake. 

To illustrate how this can be accomplished, consider the following project layout.

.. code:: text

    06_project_structure/
    ├── CMakeLists.txt        <- top level: project settings
    ├── libs/heat/            <- reusable library code
    │   ├── CMakeLists.txt
    │   ├── include/heat/
    │   └── src/
    ├── apps/                 <- programs using the library
    │   └── CMakeLists.txt
    └── tests/                <- automatic tests run with ctest
        └── CMakeLists.txt

We have three parts:

- ``libs`` -- Containing the source for reusable library code.
- ``apps`` -- Applications using our library.
- ``tests`` -- Tests for our project. 

For each subdirectory there is a separate ``CMakeLists.txt``. Let's go through them step by step. We start with the main file. First, we add the standard declaration for the project:

.. code:: cmake

    cmake_minimum_required(VERSION 3.20)

    project(HeatEquation VERSION 0.1 LANGUAGES CXX)

As this example also uses tests we add an option ``HEAT_BUILD_TESTS`` for enabling the tests of the example. We also set the output for the binary files.

.. code:: cmake

    option(HEAT_BUILD_TESTS "Build the unit tests" ON)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

Next, we add our subdirectories containing the additional ``CMakeLists.txt`` files. We use an if-statement in CMake to enable the tests when this option is set.

.. code:: cmake

    add_subdirectory(libs/heat)
    add_subdirectory(apps)

    if(HEAT_BUILD_TESTS)
        # enable_testing() must be called in the top-level CMakeLists.txt,
        # otherwise ctest will not find any tests.
        enable_testing()
        add_subdirectory(tests)
    endif()

The ``CMakeLists.txt`` files in the subdirectories are part of the main project and will have access to all variables defined in the main project, so we can define our targets just like in a single file. Note that the paths are relative to the subdirectory.

.. code:: cmake

    add_library(heat STATIC
        src/heat1d.cpp
        include/heat/heat1d.h
    )

    target_include_directories(heat PUBLIC include)
    target_compile_features(heat PUBLIC cxx_std_23)

When defining a library it can be a good idea to also define a library alias to get a clear error when linking with the library. Without an alias a wrong library name can actually succeed if there is a similar system library. Below is an example of an alias library.

.. code:: cmake

    add_library(heat::heat ALIAS heat)

The ``apps``-directory is handled in the same way.

.. code:: 

    add_executable(heat_rod heat_rod.cpp)
    target_link_libraries(heat_rod PRIVATE heat::heat)

Here we also see how the alias, ``heat::heat``, is used. 

The final subdirectory, ``tests``, contains our tests. Tests are added using the ``add_test()``-function. A test is a program that is run and returns 0 for a successful test and non-zero for a test failure. In the following code we add two tests that we link with the heat library.

.. code:: cmake

    add_executable(test_steady_state test_steady_state.cpp)
    target_link_libraries(test_steady_state PRIVATE heat::heat)
    add_test(NAME steady_state COMMAND test_steady_state)

    add_executable(test_invalid_input test_invalid_input.cpp)
    target_link_libraries(test_invalid_input PRIVATE heat::heat)
    add_test(NAME invalid_input COMMAND test_invalid_input)

It is also possible to run tests where we evaluate the output using a regular expression. This is what is done in the code below:

.. code:: cmake

    add_test(NAME heat_rod_runs COMMAND heat_rod)
    set_tests_properties(heat_rod_runs PROPERTIES PASS_REGULAR_EXPRESSION "t = +24\\.0 h")

Building is done in the same way as before. See below:

.. code:: text

    $ cmake -S . -B build
    -- The CXX compiler identification is AppleClang 17.0.0.17000603
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Check for working CXX compiler: /usr/bin/c++ - skipped
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Configuring done (0.9s)
    -- Generating done (0.0s)
    -- Build files have been written to: /Users/lindemann/Development/cpp_course/ch_cmake/06_project_structure/build
 
    $ cmake --build build --config Release
    [ 12%] Building CXX object libs/heat/CMakeFiles/heat.dir/src/heat1d.cpp.o
    [ 25%] Linking CXX static library libheat.a
    [ 25%] Built target heat
    [ 37%] Building CXX object apps/CMakeFiles/heat_rod.dir/heat_rod.cpp.o
    [ 50%] Linking CXX executable ../bin/heat_rod
    [ 50%] Built target heat_rod
    [ 62%] Building CXX object tests/CMakeFiles/test_steady_state.dir/test_steady_state.cpp.o
    [ 75%] Linking CXX executable ../bin/test_steady_state
    [ 75%] Built target test_steady_state
    [ 87%] Building CXX object tests/CMakeFiles/test_invalid_input.dir/test_invalid_input.cpp.o
    [100%] Linking CXX executable ../bin/test_invalid_input
    [100%] Built target test_invalid_input

We see here that CMake walks through the subdirectories and uses each of the provided ``CMakeLists.txt`` as if it were a single project. As the option for building tests was enabled CMake also built the test executables. 

To run the tests we need to use another CMake-provided tool, ``ctest``, as shown below.

.. code:: text

    $ ctest --test-dir build -C Release
    Test project /Users/lindemann/Development/cpp_course/ch_cmake/06_project_structure/build
        Start 1: steady_state
    1/3 Test #1: steady_state .....................   Passed    0.20 sec
        Start 2: invalid_input
    2/3 Test #2: invalid_input ....................   Passed    0.14 sec
        Start 3: heat_rod_runs
    3/3 Test #3: heat_rod_runs ....................   Passed    0.14 sec

    100% tests passed, 0 tests failed out of 3

    Total Test time (real) =   0.49 sec

.. dropdown:: Complete example: ch_cmake/06_project_structure
    :icon: code

    .. literalinclude:: ../../ch_cmake/06_project_structure/CMakeLists.txt
        :language: cmake
        :caption: CMakeLists.txt

    .. literalinclude:: ../../ch_cmake/06_project_structure/apps/CMakeLists.txt
        :language: cmake
        :caption: apps/CMakeLists.txt

    .. literalinclude:: ../../ch_cmake/06_project_structure/libs/heat/CMakeLists.txt
        :language: cmake
        :caption: libs/heat/CMakeLists.txt

    .. literalinclude:: ../../ch_cmake/06_project_structure/tests/CMakeLists.txt
        :language: cmake
        :caption: tests/CMakeLists.txt

    .. literalinclude:: ../../ch_cmake/06_project_structure/libs/heat/include/heat/heat1d.h
        :language: cpp
        :caption: libs/heat/include/heat/heat1d.h

    .. literalinclude:: ../../ch_cmake/06_project_structure/apps/heat_rod.cpp
        :language: cpp
        :caption: apps/heat_rod.cpp

    .. literalinclude:: ../../ch_cmake/06_project_structure/libs/heat/src/heat1d.cpp
        :language: cpp
        :caption: libs/heat/src/heat1d.cpp

    .. literalinclude:: ../../ch_cmake/06_project_structure/tests/test_invalid_input.cpp
        :language: cpp
        :caption: tests/test_invalid_input.cpp

    .. literalinclude:: ../../ch_cmake/06_project_structure/tests/test_steady_state.cpp
        :language: cpp
        :caption: tests/test_steady_state.cpp

.. admonition:: Key points

    * ``add_subdirectory()`` adds a directory with its own ``CMakeLists.txt``. It sees all variables of its parent.
    * Paths in a subdirectory ``CMakeLists.txt`` are relative to that subdirectory.
    * Alias targets like ``heat::heat`` give a clear error message when a library name is misspelled.
    * ``enable_testing()`` and ``add_test()`` define tests, and ``ctest`` runs them.

.. admonition:: Exercise
    :class: tip

    1. In ``ch_cmake/06_project_structure``, misspell ``heat::heat`` in ``apps/CMakeLists.txt`` and configure. Then misspell ``heat`` (without the alias) and compare the error messages.
    2. Configure with ``-DHEAT_BUILD_TESTS=OFF`` and check that the test executables are no longer built.
    3. Run a single test with ``ctest --test-dir build -R steady``.

Finding required packages
-------------------------

Many applications depend on other packages to build. Finding and configuring packages can be complicated and platform-dependent. CMake includes a mechanism for searching for packages with the ``find_package()`` function. In the easiest form you just give the name of the package that you want to find.

.. code:: cmake

    find_package(OpenMP)

If CMake doesn't find the package the configuration doesn't fail. The result of the find is stored in the variable ``OpenMP_CXX_FOUND``. We can use this to take a different configuration path.

.. code:: cmake

    find_package(OpenMP)

    if(OpenMP_CXX_FOUND)
        message(STATUS "OpenMP ${OpenMP_CXX_VERSION} found - building parallel version")
        target_link_libraries(mc_pi PRIVATE OpenMP::OpenMP_CXX)
    else()
        message(WARNING "OpenMP not found - building serial version")
    endif()    

If a package is required you can add the keyword ``REQUIRED`` to the function.

.. code:: cmake

    find_package(Threads REQUIRED)

    add_executable(mc_pi_threads mc_pi_threads.cpp)
    target_compile_features(mc_pi_threads PRIVATE cxx_std_23)
    target_link_libraries(mc_pi_threads PRIVATE Threads::Threads)

If the package can't be found, the CMake configuration will fail.

What packages are available to find is not clear cut. You can get an idea by running the following command in a terminal.

.. code:: text

    $ cmake --help-module-list
    ...
    FindALSA
    FindASPELL
    FindAVIFile
    FindArmadillo
    FindBISON
    FindBLAS
    FindBZip2
    FindBacktrace
    FindBoost
    FindBullet
    FindCABLE
    FindCUDA
    ...

The Find-modules give you a hint on what packages you can search for.

If libraries are not installed in a standard location you need to tell CMake where to find these packages. You can provide the location of the installed libraries using the ``CMAKE_PREFIX_PATH`` variable when configuring the build.

.. code:: text

    cmake -S . -B build -DCMAKE_PREFIX_PATH=/path/to/eigen/install
    cmake -S . -B build -DCMAKE_PREFIX_PATH=$CONDA_PREFIX

.. dropdown:: Complete example: ch_cmake/07_find_package_openmp
    :icon: code

    .. literalinclude:: ../../ch_cmake/07_find_package_openmp/CMakeLists.txt
        :language: cmake
        :caption: CMakeLists.txt

    .. literalinclude:: ../../ch_cmake/07_find_package_openmp/mc_pi.cpp
        :language: cpp
        :caption: mc_pi.cpp

    .. literalinclude:: ../../ch_cmake/07_find_package_openmp/mc_pi_threads.cpp
        :language: cpp
        :caption: mc_pi_threads.cpp

.. dropdown:: Complete example: ch_cmake/08_find_package_eigen
    :icon: code

    .. literalinclude:: ../../ch_cmake/08_find_package_eigen/CMakeLists.txt
        :language: cmake
        :caption: CMakeLists.txt

    .. literalinclude:: ../../ch_cmake/08_find_package_eigen/spring_chain.cpp
        :language: cpp
        :caption: spring_chain.cpp

.. admonition:: Key points

    * ``find_package()`` looks for a library installed on the system. Without ``REQUIRED`` the configure step continues even if the package is missing.
    * Found packages usually provide *imported targets*, such as ``OpenMP::OpenMP_CXX``, which are used with ``target_link_libraries()`` like any other target.
    * ``CMAKE_PREFIX_PATH`` tells CMake where to look for libraries installed in non-standard locations.

.. admonition:: Exercise
    :class: tip

    1. In ``ch_cmake/07_find_package_openmp``, configure with ``-DCMAKE_DISABLE_FIND_PACKAGE_OpenMP=ON`` to simulate a system without OpenMP. Check that the serial version is built, and compare the run times.
    2. Try to configure ``ch_cmake/08_find_package_eigen``. If Eigen is not found, install it and point CMake to it with ``CMAKE_PREFIX_PATH``.

Using the vcpkg package manager
-------------------------------

It is often very cumbersome to install packages on different platforms. To overcome this you can use the vcpkg tool to automatically download and build the dependencies. 

To install vcpkg you have to perform the following commands. The commands can differ a bit depending on platform, so check the vcpkg documentation.

.. code:: text

    $ git clone https://github.com/microsoft/vcpkg
    $ cd vcpkg
    $ git pull
    $ ./bootstrap-vcpkg.sh

When this is done set the ``VCPKG_ROOT`` environment variable to the directory of the installation.

Next, we are going to use a new feature of CMake, the ``CMakePresets.json`` file. This file simplifies the build configuration and the required options you need to specify for configuring the build. We are now going to configure a preset file for using the vcpkg package manager. The file is shown below:

.. code:: json

    {
        "version": 6,
        "configurePresets": [
            {
            "name": "vcpkg",
            "displayName": "Default (vcpkg)",
            "description": "Configure with the vcpkg toolchain. Requires the VCPKG_ROOT environment variable.",
            "binaryDir": "${sourceDir}/build",
            "toolchainFile": "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            }
        ],
        "buildPresets": [
            {
            "name": "release",
            "configurePreset": "vcpkg",
            "configuration": "Release"
            }
        ]
    }

There are two sections in this file: the first defines the configuration settings and the second the build settings.

We also need to create a ``vcpkg.json`` file containing the required packages. This file will have the following content:

.. code:: json

    {
        "name": "truss-solver",
        "version": "1.0.0",
        "description": "CMake chapter example 09: dependencies declared in a vcpkg manifest",
        "dependencies": [
            "eigen3",
            "nlohmann-json"
        ]
    }

The important entries are contained in the ``dependencies`` dictionary. Here we list that we need the ``eigen3`` and ``nlohmann-json`` libraries.  

The nice thing with using vcpkg is that we don't need to make any changes in the ``CMakeLists.txt`` file specifically for the application. The complete build is specified in the preset file. 

To illustrate the usage we are going to build an application that requires the libraries described above. 

We start with the standard configurations.

.. code:: cmake

    cmake_minimum_required(VERSION 3.20)

    project(TrussSolver LANGUAGES CXX)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

Next, we use ``find_package()`` to find and configure the required packages.

.. code:: cmake

    find_package(Eigen3 CONFIG REQUIRED)
    find_package(nlohmann_json CONFIG REQUIRED) 

As the application requires both libraries to work we give the ``REQUIRED`` attribute. The ``CONFIG`` attribute tells the command to use the library provided configuration information. 

Next, we define our target and link options. Please note that we use the new namespace method of listing libraries so we avoid clashes with system installed libraries.

.. code:: cmake

    add_executable(truss truss.cpp)
    target_compile_features(truss PRIVATE cxx_std_23)
    target_link_libraries(truss PRIVATE Eigen3::Eigen nlohmann_json::nlohmann_json)    

The application also comes with a sample configuration file ``truss.json`` which should be copied next to the executable file. This can also be handled by CMake using the ``add_custom_command()`` function. Using this command we can specify operations that can be performed before and after the build. In this case we want the file to be copied post build, so we give the attribute ``POST_BUILD`` in the call. In the attribute ``COMMAND`` we specify the command to be executed. The complete call is shown below:

.. code:: cmake

    add_custom_command(TARGET truss POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${CMAKE_CURRENT_SOURCE_DIR}/truss.json
                $<TARGET_FILE_DIR:truss>
        COMMENT "Copying truss.json to the output directory"
    )    

To configure and build our application using the preset we give the following commands:

.. code:: text

    $ export VCPKG_ROOT=/Users/lindemann/vcpkg
    $ cmake --preset vcpkg
    -- Running vcpkg install
    Detecting compiler hash for triplet arm64-osx...
    Compiler found: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++
    The following packages will be built and installed:
        eigen3:arm64-osx@5.0.1
        nlohmann-json:arm64-osx@3.12.0#2

    [ ---- cut ---- ]

    Waiting for 1 remaining binary cache submissions...
    Completed submission of eigen3:arm64-osx@5.0.1 to 1 binary cache(s) in 251 ms (1/1)
    All requested installations completed successfully in: 2.6 s
    -- Running vcpkg install - done
    -- The CXX compiler identification is AppleClang 17.0.0.17000603
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Check for working CXX compiler: /usr/bin/c++ - skipped
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Found nlohmann_json: /Users/lindemann/Development/cpp_course/ch_cmake/09_vcpkg_manifest/build/vcpkg_installed/arm64-osx/share/nlohmann_json/nlohmann_jsonConfig.cmake (found version "3.12.0")
    -- Configuring done (5.2s)
    -- Generating done (0.0s)
    -- Build files have been written to: /Users/lindemann/Development/cpp_course/ch_cmake/09_vcpkg_manifest/build

Please note that the vcpkg configuration will print out the ``CMakeLists.txt`` function calls required to configure and find the packages as shown below:

.. code:: text

    # this is heuristically generated, and may not be correct
    find_package(Eigen3 CONFIG REQUIRED)
    target_link_libraries(main PRIVATE Eigen3::Eigen)

    eigen3 provides pkg-config modules:

    # A C++ template library for linear algebra: vectors, matrices, and related algorithms
    eigen3

    The package nlohmann-json provides CMake targets:

        find_package(nlohmann_json CONFIG REQUIRED)
        target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)

    The package nlohmann-json can be configured to not provide implicit conversions via a custom triplet file:

        set(nlohmann-json_IMPLICIT_CONVERSIONS OFF)

    For more information, see the docs here:

        https://json.nlohmann.me/api/macros/json_use_implicit_conversions/

To build the package we also use the preset configuration:

.. code:: text

    $ cmake --build --preset release
    [ 50%] Building CXX object CMakeFiles/truss.dir/truss.cpp.o
    [100%] Linking CXX executable bin/truss
    Copying truss.json to the output directory
    [100%] Built target truss

We also see that the ``truss.json`` file is automatically copied to the same directory as the application binary.

.. dropdown:: Complete example: ch_cmake/09_vcpkg_manifest
    :icon: code

    .. literalinclude:: ../../ch_cmake/09_vcpkg_manifest/CMakeLists.txt
        :language: cmake
        :caption: CMakeLists.txt

    .. literalinclude:: ../../ch_cmake/09_vcpkg_manifest/CMakePresets.json
        :language: json
        :caption: CMakePresets.json

    .. literalinclude:: ../../ch_cmake/09_vcpkg_manifest/truss.json
        :language: json
        :caption: truss.json

    .. literalinclude:: ../../ch_cmake/09_vcpkg_manifest/vcpkg.json
        :language: json
        :caption: vcpkg.json

    .. literalinclude:: ../../ch_cmake/09_vcpkg_manifest/truss.cpp
        :language: cpp
        :caption: truss.cpp

.. admonition:: Key points

    * vcpkg downloads and builds the dependencies listed in ``vcpkg.json`` during the configure step.
    * vcpkg is enabled through a toolchain file, conveniently set in a ``CMakePresets.json`` file. ``CMakeLists.txt`` still uses ordinary ``find_package()`` calls.
    * Presets are used with ``cmake --preset <name>`` and ``cmake --build --preset <name>``.
    * ``add_custom_command()`` can run commands before or after a target is built, for example to copy data files.

.. admonition:: Exercise
    :class: tip

    1. In ``ch_cmake/09_vcpkg_manifest``, list the available presets with ``cmake --list-presets``.
    2. Add the ``fmt`` library to ``vcpkg.json``, find it with ``find_package(fmt CONFIG REQUIRED)``, link with ``fmt::fmt`` and use ``fmt::print()`` in ``truss.cpp``.

Downloading dependencies using FetchContent
-------------------------------------------

Another option to handle dependencies automatically is to use the FetchContent functionality of CMake. Using this method we can download libraries and automatically build them together with the application. To illustrate this we will go through a complete example. First we declare the normal CMake declarations. 

.. code:: cmake

    cmake_minimum_required(VERSION 3.20)

    project(Projectile LANGUAGES CXX)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

To use FetchContent we must first include the CMake module using the ``include()`` function. 

.. code:: cmake

    include(FetchContent)

Next, we need to declare the URL and version to download from GitHub. A typical declaration is shown below:

.. code:: cmake

    FetchContent_Declare(cli11
        URL https://github.com/CLIUtils/CLI11/archive/refs/tags/v2.4.2.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )

In the next step we download (first time only) the dependency and make the targets available to our build. 

.. code:: cmake

    FetchContent_MakeAvailable(cli11)

All targets available in the archive are now available for us to use directly in our application as well. See below:

.. code:: cmake

    add_executable(projectile projectile.cpp)
    target_compile_features(projectile PRIVATE cxx_std_23)
    target_link_libraries(projectile PRIVATE CLI11::CLI11)

We build the project just like before:

.. code:: text

    $ cmake -S . -B build
    -- The CXX compiler identification is AppleClang 17.0.0.17000603
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Check for working CXX compiler: /usr/bin/c++ - skipped
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    CMake Deprecation Warning at build/_deps/cli11-src/CMakeLists.txt:1 (cmake_minimum_required):
    Compatibility with CMake < 3.10 will be removed from a future version of
    CMake.

    Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
    to tell CMake that the project requires at least <min> but has been updated
    to work with policies introduced by <max> or earlier.


    -- Configuring done (1.5s)
    -- Generating done (0.0s)
    -- Build files have been written to: /Users/lindemann/Development/cpp_course/ch_cmake/10_fetchcontent/build

    $ cmake --build build
    [  0%] Built target CLI11
    [ 50%] Building CXX object CMakeFiles/projectile.dir/projectile.cpp.o
    [100%] Linking CXX executable bin/projectile
    [100%] Built target projectile

As we can see, the CMake files from the CLI project are a bit outdated, but it downloaded and built the library.

.. dropdown:: Complete example: ch_cmake/10_fetchcontent
    :icon: code

    .. literalinclude:: ../../ch_cmake/10_fetchcontent/CMakeLists.txt
        :language: cmake
        :caption: CMakeLists.txt

    .. literalinclude:: ../../ch_cmake/10_fetchcontent/projectile.cpp
        :language: cpp
        :caption: projectile.cpp

.. admonition:: Key points

    * FetchContent downloads a dependency during the configure step and builds it together with your project.
    * ``FetchContent_Declare()`` says where to get the dependency, and ``FetchContent_MakeAvailable()`` downloads it and makes its targets available.
    * The download only happens the first time. The source code is stored in ``build/_deps``.

.. admonition:: Exercise
    :class: tip

    1. In ``ch_cmake/10_fetchcontent``, look in ``build/_deps`` to see what was downloaded.
    2. Change the CLI11 version in ``FetchContent_Declare()`` to a newer release, delete the build directory and build again.

Unit-testing with CTest and Catch2
----------------------------------

We have already covered basic test functionality of CMake using ``ctest``. However, for numerical libraries it is more complicated to implement these tests. To make it easier to write tests for these libraries we can use the Catch2 test framework to help us. To illustrate how to use this framework we implement test functions for a quadrature library. The tests can be implemented in separate source files or in a single source. In this example we will provide the test cases in a single source file ``test_quadrature.cpp``. First, we add all required include files:

.. code:: cpp

    #include <quadrature.h>

    #include <catch2/catch_test_macros.hpp>
    #include <catch2/matchers/catch_matchers_floating_point.hpp>

    #include <cmath>
    #include <numbers>
    #include <stdexcept>

    using Catch::Matchers::WithinAbs;
    using Catch::Matchers::WithinRel;

    // Floating point results must never be compared with ==. Catch2
    // provides matchers for absolute and relative tolerances.    

The concept is that we define test cases where we call our libraries and evaluate the functionality. A test is defined using the macro ``TEST_CASE()``. In the test we perform our function call which we then evaluate with ``REQUIRE_XXX()`` macros. Below is a simple example of a test case.

.. code:: cpp

    TEST_CASE("Trapezoidal rule is exact for linear functions", "[trapezoidal]")
    {
        auto f = [](double x) { return 3.0 * x + 2.0; };
        REQUIRE_THAT(quad::trapezoidal(f, 0.0, 2.0, 1), WithinAbs(10.0, 1e-12));
    }

In this case we require that the result from a call to ``quad::trapezoidal(f, 0.0, 2.0, 1)`` is ``10.0`` with an absolute tolerance of ``1e-12``. 

To implement the test functionality in our ``CMakeLists.txt`` we use FetchContent to download and install the Catch2 framework.

.. code:: cmake

    enable_testing()

    include(FetchContent)
    FetchContent_Declare(Catch2
        URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.7.1.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(Catch2)

    add_executable(test_quadrature tests/test_quadrature.cpp)

    # Catch2::Catch2WithMain provides main(), so the test file only
    # contains test cases.
    target_link_libraries(test_quadrature PRIVATE quadrature Catch2::Catch2WithMain)

    # catch_discover_tests() asks the test program which test cases it
    # contains and registers each of them as a separate CTest test.
    # Compared to a single add_test() this gives a clear report of
    # exactly which test case failed.
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    include(Catch)
    catch_discover_tests(test_quadrature)

We can now build and test our library.

.. code:: text

    $ cmake --build build --config Release
    [  2%] Built target quadrature
    [ 96%] Built target Catch2
    [ 98%] Built target Catch2WithMain
    [100%] Built target test_quadrature    

    $ ctest --test-dir build -C Release --output-on-failure
    Test project /Users/lindemann/Development/cpp_course/ch_cmake/11_testing/build
        Start 1: Trapezoidal rule is exact for linear functions
    1/7 Test #1: Trapezoidal rule is exact for linear functions ..........   Passed    0.01 sec
        Start 2: Simpson's rule is exact for cubic polynomials
    2/7 Test #2: Simpson's rule is exact for cubic polynomials ...........   Passed    0.00 sec
        Start 3: Gauss-Legendre 2-point is exact for cubic polynomials
    3/7 Test #3: Gauss-Legendre 2-point is exact for cubic polynomials ...   Passed    0.00 sec
        Start 4: Methods agree on the integral of sin(x) over [0, pi]
    4/7 Test #4: Methods agree on the integral of sin(x) over [0, pi] ....   Passed    0.00 sec
        Start 5: Trapezoidal rule converges with order 2
    5/7 Test #5: Trapezoidal rule converges with order 2 .................   Passed    0.00 sec
        Start 6: Simpson's rule converges with order 4
    6/7 Test #6: Simpson's rule converges with order 4 ...................   Passed    0.00 sec
        Start 7: Invalid number of intervals throws
    7/7 Test #7: Invalid number of intervals throws ......................   Passed    0.00 sec

    100% tests passed, 0 tests failed out of 7

    Total Test time (real) =   0.04 sec

.. dropdown:: Complete example: ch_cmake/11_testing
    :icon: code

    .. literalinclude:: ../../ch_cmake/11_testing/CMakeLists.txt
        :language: cmake
        :caption: CMakeLists.txt

    .. literalinclude:: ../../ch_cmake/11_testing/include/quadrature.h
        :language: cpp
        :caption: include/quadrature.h

    .. literalinclude:: ../../ch_cmake/11_testing/src/quadrature.cpp
        :language: cpp
        :caption: src/quadrature.cpp

    .. literalinclude:: ../../ch_cmake/11_testing/tests/test_quadrature.cpp
        :language: cpp
        :caption: tests/test_quadrature.cpp

.. admonition:: Key points

    * Catch2 test cases are defined with ``TEST_CASE()`` and checked with ``REQUIRE()`` and ``REQUIRE_THAT()``.
    * Floating-point results should be compared with a tolerance using Catch2 matchers, never with ``==``.
    * ``catch_discover_tests()`` registers each test case as a separate CTest test.
    * ``ctest --output-on-failure`` shows the output of failing tests.

.. admonition:: Exercise
    :class: tip

    1. In ``ch_cmake/11_testing``, add a test case that fails on purpose and read the output of ``ctest --test-dir build -C Release --output-on-failure``.
    2. Run only the tests for Simpson's rule with ``ctest --test-dir build -C Release -R Simpson``.
    3. Write a test case checking that all three methods compute the integral of :math:`e^x` over :math:`[0, 1]`, which is :math:`e - 1`, to a relative tolerance of ``1e-6``.

Build configurations
--------------------

Install and export
------------------

C++ and Fortran
---------------


Quick reference
---------------

Command line
~~~~~~~~~~~~

.. list-table::
    :header-rows: 1
    :widths: 50 50

    * - Command
      - Description
    * - ``cmake -S . -B build``
      - Configure the project in the current directory into ``build``.
    * - ``cmake -S . -B build -G Ninja``
      - Configure with a specific generator.
    * - ``cmake -S . -B build -DNAME=VALUE``
      - Set an option or a cache variable, e.g. ``-DBUILD_SHARED_LIBS=ON``.
    * - ``cmake --build build``
      - Build all targets.
    * - ``cmake --build build --config Release``
      - Build the Release configuration (Visual Studio and Xcode).
    * - ``cmake --build build --target name``
      - Build a single target.
    * - ``cmake --build build --parallel``
      - Build using several processor cores.
    * - ``cmake --list-presets``
      - List the configure presets in ``CMakePresets.json``.
    * - ``cmake --preset name``
      - Configure using a preset.
    * - ``cmake --build --preset name``
      - Build using a build preset.
    * - ``ctest --test-dir build -C Release``
      - Run all tests.
    * - ``ctest --test-dir build -R regex``
      - Run the tests whose names match a regular expression.
    * - ``ctest --test-dir build --output-on-failure``
      - Show the output of failing tests.
    * - ``cmake --help-module-list``
      - List the modules shipped with CMake, including the Find-modules.

CMake commands
~~~~~~~~~~~~~~

.. list-table::
    :header-rows: 1
    :widths: 50 50

    * - Command
      - Description
    * - ``cmake_minimum_required(VERSION 3.20)``
      - Oldest CMake version the project supports. Always the first line.
    * - ``project(Name VERSION 1.0 LANGUAGES CXX)``
      - Project name, version and languages.
    * - ``add_executable(name src...)``
      - Create an executable target.
    * - ``add_library(name [STATIC|SHARED] src...)``
      - Create a library target.
    * - ``add_library(ns::name ALIAS name)``
      - Create an alias for a library target.
    * - ``target_include_directories(t PRIVATE|PUBLIC dir...)``
      - Where the compiler finds header files.
    * - ``target_compile_features(t PRIVATE|PUBLIC cxx_std_23)``
      - Required C++ standard.
    * - ``target_compile_options(t PRIVATE flags...)``
      - Extra compiler flags.
    * - ``target_link_libraries(t PRIVATE|PUBLIC lib...)``
      - Link with libraries and use their public properties.
    * - ``set_target_properties(t PROPERTIES ...)``
      - Set other target properties.
    * - ``add_subdirectory(dir)``
      - Process the ``CMakeLists.txt`` in a subdirectory.
    * - ``option(NAME "description" ON)``
      - Define an option the user can set on the command line.
    * - ``find_package(Name [CONFIG] [REQUIRED])``
      - Find a library installed on the system.
    * - ``FetchContent_Declare()`` / ``FetchContent_MakeAvailable()``
      - Download a dependency and build it with the project.
    * - ``add_custom_command(TARGET t POST_BUILD COMMAND ...)``
      - Run a command after a target has been built.
    * - ``enable_testing()`` / ``add_test(NAME n COMMAND cmd)``
      - Define tests to be run by CTest.
