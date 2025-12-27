# Building the C++ Course Examples

This project uses CMake with vcpkg as the package manager. The build system is designed to automatically detect vcpkg and work with standard CMake commands.

## Prerequisites

1. **CMake** (version 3.20 or higher)
2. **vcpkg** package manager
3. **C++ compiler** (MSVC, GCC, or Clang)
4. **Ninja** build system (optional but recommended)

## Setting up vcpkg

The CMake configuration will automatically detect vcpkg if:
- The `VCPKG_ROOT` environment variable is set, or
- vcpkg is installed in one of these locations:
  - `${PROJECT_DIR}/vcpkg/`
  - `C:/vcpkg/` or `E:/vcpkg/` (Windows)
  - `$HOME/vcpkg/` or `/opt/vcpkg/` (Linux/macOS)

### Setting VCPKG_ROOT (Recommended)

**Windows (Command Prompt):**
```cmd
set VCPKG_ROOT=E:\vcpkg
```

**Windows (PowerShell):**
```powershell
$env:VCPKG_ROOT = "E:\vcpkg"
```

**Linux/macOS:**
```bash
export VCPKG_ROOT=/path/to/vcpkg
```

To make it permanent, add the above line to your `.bashrc` or `.zshrc`.

## Building with CMake

### Option 1: Using CMake Presets (Recommended)

List available presets:
```bash
cmake --list-presets
```

Configure with a preset:
```bash
cmake --preset debug
# or
cmake --preset release
# or
cmake --preset vs2022
```

Build:
```bash
cmake --build --preset debug
# or
cmake --build --preset release
```

### Option 2: Standard CMake Commands

**Configure:**
```bash
# Debug build
cmake -B build-debug -DCMAKE_BUILD_TYPE=Debug

# Release build
cmake -B build-release -DCMAKE_BUILD_TYPE=Release
```

**Build:**
```bash
cmake --build build-debug
# or
cmake --build build-release
```

### Option 3: Manual vcpkg Toolchain

If vcpkg is not autodetected, you can specify the toolchain file manually:
```bash
cmake -B build-debug -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
```

## Build Options

The following CMake options control which examples are built:

- `BUILD_QT_EXAMPLES` (default: ON) - Build Qt-based examples
- `BUILD_VTK_EXAMPLES` (default: OFF) - Build VTK visualization examples
- `BUILD_EIGEN_EXAMPLES` (default: ON) - Build Eigen linear algebra examples
- `BUILD_MIXED_LANG_EXAMPLES` (default: OFF) - Build mixed-language examples

Example:
```bash
cmake -B build-debug -DBUILD_VTK_EXAMPLES=ON -DBUILD_QT_EXAMPLES=OFF
```

## Output

All executables are built to the `bin/` directory in the project root.

## Troubleshooting

**vcpkg not found:**
- Set the `VCPKG_ROOT` environment variable
- Or use `-DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake`

**Missing dependencies:**
```bash
cd /path/to/vcpkg
./vcpkg install
```

This will install all dependencies listed in `vcpkg.json`.

## Legacy Build Scripts

The old build scripts (`cpp-build.cmd`, `config_debug_build.cmd`, etc.) are kept for backward compatibility but are no longer needed with the modernized build system.
