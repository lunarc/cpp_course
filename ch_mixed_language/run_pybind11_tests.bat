@echo off
REM Script to run pybind11 Python tests
REM This assumes you're running from the build directory

echo ====================================
echo PyBind11 Examples Test Runner
echo ====================================
echo.

REM Detect the module location
set MODULE_DIR=%~dp0
if exist "%MODULE_DIR%bin" (
    set MODULE_DIR=%MODULE_DIR%bin
) else if exist "%MODULE_DIR%Release" (
    set MODULE_DIR=%MODULE_DIR%Release
) else if exist "%MODULE_DIR%Debug" (
    set MODULE_DIR=%MODULE_DIR%Debug
)

echo Using module directory: %MODULE_DIR%
echo.

REM Set PYTHONPATH to include the module directory
set PYTHONPATH=%MODULE_DIR%;%PYTHONPATH%

REM Check for Python
python --version >nul 2>&1
if errorlevel 1 (
    echo Error: Python not found in PATH
    echo Please install Python 3.6 or later
    pause
    exit /b 1
)

echo Testing basic point module...
echo.
python "%MODULE_DIR%\test_point_basic.py"
if errorlevel 1 (
    echo.
    echo Error running basic test. Make sure pybind11 modules are built.
    echo Enable with: cmake -DBUILD_PYBIND11_EXAMPLES=ON ..
    pause
    exit /b 1
)

echo.
echo ====================================
echo.

echo Testing advanced point module...
echo.
python "%MODULE_DIR%\test_point_advanced.py"
if errorlevel 1 (
    echo.
    echo Error running advanced test.
    pause
    exit /b 1
)

echo.
echo ====================================
echo All tests completed successfully!
echo ====================================
pause
