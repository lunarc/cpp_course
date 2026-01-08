#!/bin/bash
# Script to run pybind11 Python tests
# This assumes you're running from the build directory

echo "===================================="
echo "PyBind11 Examples Test Runner"
echo "===================================="
echo

# Detect the module location
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
if [ -d "$SCRIPT_DIR/bin" ]; then
    MODULE_DIR="$SCRIPT_DIR/bin"
elif [ -d "$SCRIPT_DIR/Release" ]; then
    MODULE_DIR="$SCRIPT_DIR/Release"
elif [ -d "$SCRIPT_DIR/Debug" ]; then
    MODULE_DIR="$SCRIPT_DIR/Debug"
else
    MODULE_DIR="$SCRIPT_DIR"
fi

echo "Using module directory: $MODULE_DIR"
echo

# Set PYTHONPATH to include the module directory
export PYTHONPATH="$MODULE_DIR:$PYTHONPATH"

# Check for Python
if ! command -v python3 &> /dev/null; then
    echo "Error: python3 not found in PATH"
    echo "Please install Python 3.6 or later"
    exit 1
fi

echo "Testing basic point module..."
echo
python3 "$MODULE_DIR/test_point_basic.py"
if [ $? -ne 0 ]; then
    echo
    echo "Error running basic test. Make sure pybind11 modules are built."
    echo "Enable with: cmake -DBUILD_PYBIND11_EXAMPLES=ON .."
    exit 1
fi

echo
echo "===================================="
echo

echo "Testing advanced point module..."
echo
python3 "$MODULE_DIR/test_point_advanced.py"
if [ $? -ne 0 ]; then
    echo
    echo "Error running advanced test."
    exit 1
fi

echo
echo "===================================="
echo "All tests completed successfully!"
echo "===================================="
