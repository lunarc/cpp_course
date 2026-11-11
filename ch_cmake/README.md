# CMake examples

Example projects for the CMake chapter. Each directory is a complete,
standalone CMake project. The examples are **not** part of the course's
top-level `CMakeLists.txt`; build each one on its own.

They build on each other, so work through them in order.

| #  | Directory                 | Topic                                                                       | New CMake commands                                                                                  |
|----|---------------------------|-----------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------|
| 01 | `01_single_target`        | Smallest possible project, configure and build steps                        | `cmake_minimum_required`, `project`, `add_executable`                                               |
| 02 | `02_multiple_sources`     | One program from several `.cpp`/`.h` files, C++23 standard                  | `CMAKE_CXX_STANDARD`, `target_include_directories`                                                  |
| 03 | `03_multiple_targets`     | Several programs in one project, building a single target, warnings         | `CMAKE_RUNTIME_OUTPUT_DIRECTORY`, `target_compile_options`, `foreach`, `if(MSVC)`                   |
| 04 | `04_static_library`       | Putting shared code in a library, PUBLIC vs PRIVATE                         | `add_library(STATIC)`, `target_link_libraries`, `target_compile_features`                           |
| 05 | `05_shared_library`       | Shared libraries/DLLs, symbol export, run-time lookup                       | `BUILD_SHARED_LIBS`, `option`, `GenerateExportHeader`, `set_target_properties`                      |
| 06 | `06_project_structure`    | Subdirectories (libs/apps/tests) and simple tests with CTest                | `add_subdirectory`, `ALIAS` targets, `enable_testing`, `add_test`                                   |
| 07 | `07_find_package_openmp`  | Dependencies provided by the compiler/system: OpenMP and threads            | `find_package`, imported targets, optional dependencies                                             |
| 08 | `08_find_package_eigen`   | An installed third-party library: Eigen                                     | `find_package(... CONFIG REQUIRED)`, `CMAKE_PREFIX_PATH`                                            |
| 09 | `09_vcpkg_manifest`       | Dependencies installed automatically by vcpkg (Eigen + nlohmann/json)       | `vcpkg.json`, toolchain files, `CMakePresets.json`, `add_custom_command`, generator expressions     |
| 10 | `10_fetchcontent`         | Downloading a dependency (CLI11) during configuration                       | `FetchContent_Declare`, `FetchContent_MakeAvailable`                                                |
| 11 | `11_testing`              | Unit tests for numerical code with Catch2                                   | `catch_discover_tests`, `ctest --output-on-failure`                                                 |
| 12 | `12_build_configuration`  | Debug/Release, user options, generated config header, presets               | `CMAKE_BUILD_TYPE`, `configure_file`, `target_compile_definitions`, `$<CONFIG>`, `$<CXX_COMPILER_ID>` |
| 13 | `13_install_and_export`   | Installing a library and using it from another project                      | `install`, `GNUInstallDirs`, `CMakePackageConfigHelpers`, `$<BUILD_INTERFACE>`                      |
| 14 | `14_cpp_and_fortran`      | Mixing C++ and Fortran                                                      | `project(... Fortran)`, `bind(C)`, Fortran modules                                                  |

## Building an example

All examples use the same two commands, run from inside the example
directory:

```bash
cmake -S . -B build                    # configure
cmake --build build --config Release   # build
```

Each `CMakeLists.txt` starts with a comment block containing the exact
commands for that example, including any extra steps (running tests,
installing, choosing a preset).

Where the program ends up depends on the generator:

* Makefiles / Ninja: `build/` or `build/bin/`
* Visual Studio: `build/Release/` or `build/bin/Release/`

## Requirements

* CMake 3.20 or newer
* A C++23 compiler with `<print>` support (GCC 14+, Clang 18+ with libc++ 18+
  or libstdc++ 14+, MSVC 2022 17.7+). The examples use `std::print`/`std::println`
  for output.
* Example 14 only needs C++20 and uses `std::cout`, since Fortran toolchains
  (e.g. MinGW gfortran 11/13) often come with an older C++ library.
* Example 08: Eigen installed (system package manager, conda or vcpkg)
* Example 09: vcpkg, with the `VCPKG_ROOT` environment variable set
* Examples 10 and 11: internet access the first time they are configured
* Example 12 presets: the Ninja build tool
* Example 14: a Fortran compiler (gfortran, ifx or flang)

## Ideas for more examples

Topics that could be added later:

* **Python bindings with pybind11/nanobind**: `find_package(Python)`,
  `pybind11_add_module`. Exposes a C++ solver to Python/NumPy users.
  (See also `ch_mixed_language`.)
* **MPI**: `find_package(MPI)`, `MPI::MPI_CXX`, running tests with
  `mpiexec` through CTest.
* **CUDA**: `project(... LANGUAGES CXX CUDA)`, `CMAKE_CUDA_ARCHITECTURES`.
* **Sanitizers and debugging builds**: an option that adds
  `-fsanitize=address,undefined` for finding memory errors.
* **Performance flags**: `CheckIPOSupported` for link-time optimisation,
  and the risks of `-march=native` and `-ffast-math` for reproducibility.
* **Code generation and data files**: `add_custom_command` to generate
  sources or lookup tables at build time.
* **Documentation**: building Doxygen documentation with
  `find_package(Doxygen)` and `doxygen_add_docs`.
* **Packaging**: CPack to create a zip, `.deb` or installer.
* **Qt and VTK applications**: `qt_add_executable`, `AUTOMOC`, `vtk_module_autoinit`
  (connects to `ch_qt` and `ch_vtk`).
* **IDE integration**: opening a CMake project directly in VS Code,
  Visual Studio, CLion or Qt Creator.
