Build C++ code examples
=======================

This book comes with an extensive set of examples that demonstrate how to use C++. The examples are organized by chapter and are located in directories prefixed with ``ch_``. The examples are built using CMake, which is a cross-platform build system. CMake is a powerful tool that can generate build files for a variety of build systems, including Makefiles, Ninja, and Visual Studio solutions.

In the following sections shows how to build the examples using a special helper script called ``cpp-build``. This script is located in the root directory of the book's repository. The script builds all the examples in the book and places the executables in the ``bin`` directory and the build files in the ``build-debug`` and ``build-release`` directories.

Building on Windows
-------------------

The Windows build relies on the package manager Vcpkg to install the necessary dependencies. The script automatically installs Vcpkg and the dependencies if they are not already installed. The script also sets the necessary environment variables to find the dependencies.

Before running the build script on Windows you will first need to install the Vcpkg tool. To install Vcpkg, follow these steps:

1. Clone the Vcpkg repository from GitHub:

   .. code-block:: bash

      git clone

2. Change to the Vcpkg directory:
3. Run the bootstrap script:

   .. code-block:: bash

      .\bootstrap-vcpkg.bat

4. Run the Vcpkg integration script:
5. Run the Vcpkg integration script:

   .. code-block:: bash

      .\vcpkg integrate install

6. Add the Vcpkg directory to the system path:

   .. code-block:: bash

      set PATH=%PATH%;C:\path\to\vcpkg

To build the dependencies go to the root directory of the book's repository and run the following command:

.. code-block:: bash

   vcpkg install

This will install all the dependencies needed to build the examples. This can take a while, so be patient.

To build the debug versions of the examples, run the following command:

.. code-block:: bash

   cpp-build --build --build-type=Debug

To build the release versions of the examples, run the following command:

.. code-block:: bash

   cpp-build --build --build-type=Release

The finished examples will be located in the ``bin`` directory.

To open the Visual Studio solution, go to the ``build-debug`` or ``build-release`` directory and open the ``cpp_examples.sln`` file by typing it in the command line or by double-clicking it in the file explorer.

Building on Linux
-----------------

To build the examples on Linux, you will need to install the necessary dependencies. The examples will require a recent version of CMake, a C++ compiler, and the following libraries:

- Eigen3
- Qt 

To install the dependencies on Ubuntu, run the following command:

.. code-block:: bash

   sudo apt-get install cmake g++ libeigen3-dev qt5-default

To build the debug versions of the examples, run the following command:

.. code-block:: bash

   ./cpp-build --build --build-type=Debug

To build the release versions of the examples, run the following command:

.. code-block:: bash

   ./cpp-build --build --build-type=Release

The finished examples will be located in the ``bin`` directory.

