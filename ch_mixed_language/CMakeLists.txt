add_executable(mixed1 mixed1.cpp c_mixed.c c_mixed.h)
add_executable(mixed2 mixed2.c point.h point.cpp)

set_target_properties(
    mixed1 
    mixed2
    PROPERTIES
    FOLDER "ch_mixed_language"
)

# PyBind11 examples (optional)
if(BUILD_PYBIND11_EXAMPLES)
    message(STATUS "Building pybind11 examples in ch_mixed_language")
    
    # Find Python and pybind11
    # IMPORTANT: vcpkg Python only provides release libraries
    # Force Python to use release mode even in debug builds
    set(Python_USE_DEBUG_LIBS OFF)
    find_package(Python COMPONENTS Interpreter Development REQUIRED)
    find_package(pybind11 CONFIG REQUIRED)
    
    # Basic example: Simple Point binding
    pybind11_add_module(point_module point_python.cpp point.cpp)
    set_target_properties(point_module PROPERTIES
        FOLDER "ch_mixed_language"
        OUTPUT_NAME "point_module"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
        LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release"
        # Use release runtime libraries to match Python
        MSVC_RUNTIME_LIBRARY "MultiThreadedDLL"
    )
    
    # Advanced example: Point and PointCloud with properties and special methods
    pybind11_add_module(point_advanced point_python_advanced.cpp point_advanced.cpp)
    set_target_properties(point_advanced PROPERTIES
        FOLDER "ch_mixed_language"
        OUTPUT_NAME "point_advanced"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
        LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release"
        # Use release runtime libraries to match Python
        MSVC_RUNTIME_LIBRARY "MultiThreadedDLL"
    )
    
    # Copy Python test scripts to build directory
    configure_file(test_point_basic.py ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_point_basic.py COPYONLY)
    configure_file(test_point_advanced.py ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_point_advanced.py COPYONLY)
    
    message(STATUS "PyBind11 modules will be built: point_module, point_advanced")
    message(STATUS "Python test scripts copied to: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    message(STATUS "Note: Modules use Release runtime (/MD) to match vcpkg Python")
endif()