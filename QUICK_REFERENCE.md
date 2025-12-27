# Quick Reference - Building C++ Course Examples

## Prerequisites Setup

### Set vcpkg location (one-time setup)
**Windows (permanent):**
```cmd
setx VCPKG_ROOT "E:\vcpkg"
```

**Linux/macOS (add to ~/.bashrc or ~/.zshrc):**
```bash
export VCPKG_ROOT=/path/to/vcpkg
```

## Common Commands

### Using CMake Presets (Recommended)

```bash
# List available presets
cmake --list-presets

# Configure debug build
cmake --preset debug

# Build debug
cmake --build --preset debug

# Configure release build
cmake --preset release

# Build release
cmake --build --preset release
```

### Using Standard CMake

```bash
# Configure
cmake -B build-debug -DCMAKE_BUILD_TYPE=Debug

# Build
cmake --build build-debug

# Parallel build (faster)
cmake --build build-debug -j8
```

### Windows Convenience Scripts

```cmd
# Build debug
build-debug.cmd

# Build release
build-release.cmd

# Configure only
configure.cmd debug

# Clean all
clean.cmd
```

## Build Options

```bash
# Disable Qt examples
cmake --preset debug -DBUILD_QT_EXAMPLES=OFF

# Enable VTK examples
cmake --preset debug -DBUILD_VTK_EXAMPLES=ON

# Custom configuration
cmake -B build \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_QT_EXAMPLES=ON \
  -DBUILD_VTK_EXAMPLES=OFF \
  -DBUILD_EIGEN_EXAMPLES=ON
```

## Troubleshooting

```bash
# Verify vcpkg detection
cmake --preset debug 2>&1 | findstr vcpkg

# Manually specify vcpkg
cmake -B build -DCMAKE_TOOLCHAIN_FILE=E:/vcpkg/scripts/buildsystems/vcpkg.cmake

# Clean and rebuild
clean.cmd
cmake --preset debug
cmake --build --preset debug
```

## Running Examples

All executables are in `bin/` directory:

```bash
# Windows
cd bin
.\example_name.exe

# Linux/macOS
cd bin
./example_name
```
