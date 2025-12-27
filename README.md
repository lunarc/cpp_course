# C++ for Scientists and Engineers

This course is intended as an introduction to C++ for engineers or researchers using the language to develop computational applications or workflows requiring a high-performance language. The target audience are existing users of Python, NumPy and Matplotlib.

The course gives a thorough introduction to C++ covering both classic as well modern features of the language. The focus is on tools required to develop computational codes using established libraries for array computing (Eigen), user interface design (Qt) and visualization (VTK).

The course focuses a lot on complete examples of code that are ready to run. In addition, the course documentation is complemented with a complete source code tree on GitHub with all of the examples described in the course.

Jonas Lindemann, 2024
## Building the Examples

This project uses a modern CMake-based build system with vcpkg package management. For detailed build instructions, see [BUILD.md](BUILD.md).

### Quick Start

**Prerequisites:** CMake 3.20+, vcpkg, and a C++ compiler

**Set vcpkg location (if not in standard location):**
```bash
# Windows
set VCPKG_ROOT=E:\vcpkg

# Linux/macOS
export VCPKG_ROOT=/path/to/vcpkg
```

**Build:**
```bash
# Using presets (recommended)
cmake --preset debug
cmake --build --preset debug

# Or using standard CMake
cmake -B build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug
```

Executables will be in the `bin/` directory.