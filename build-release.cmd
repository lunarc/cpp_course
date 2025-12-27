@echo off
REM Modern build script using CMake presets

set VCPKG_ROOT=E:\vcpkg

echo Configuring Release build...
cmake --preset vs2026-release
if %errorlevel% neq 0 (
    echo Configuration failed!
    exit /b %errorlevel%
)

echo.
echo Building Release configuration...
cmake --build --preset vs2026-release
if %errorlevel% neq 0 (
    echo Build failed!
    exit /b %errorlevel%
)

echo.
echo Build completed successfully!
echo Executables are in the bin/ directory
