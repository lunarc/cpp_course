@echo off
REM Configure the project using CMake presets

if "%1"=="" (
    echo Usage: configure.cmd [preset]
    echo.
    echo Available presets:
    cmake --list-presets
    exit /b 1
)

echo Configuring with preset: %1
cmake --preset %1

if %errorlevel% neq 0 (
    echo Configuration failed!
    exit /b %errorlevel%
)

echo.
echo Configuration completed successfully!
echo To build, run: cmake --build --preset %1
