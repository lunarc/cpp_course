# Migration Guide - New Build System

## What Changed?

The build system has been modernized to use standard CMake commands with automatic vcpkg detection.

### Old Way
```cmd
# Old scripts with hardcoded paths
cpp-build.cmd
config_debug_build.cmd
```

### New Way
```cmd
# Standard CMake commands
cmake --preset debug
cmake --build --preset debug

# Or convenience scripts
build-debug.cmd
build-release.cmd
```

## Key Improvements

1. **Automatic vcpkg Detection**: No need to hardcode vcpkg paths in CMakePresets.json
2. **Standard CMake**: Works with any IDE or build tool that supports CMake
3. **Cross-Platform**: Same commands work on Windows, Linux, and macOS
4. **Flexible**: Easy to customize build options

## Migration Steps

### 1. Set VCPKG_ROOT Environment Variable (Recommended)

**Windows:**
```cmd
setx VCPKG_ROOT "E:\vcpkg"
```
Then restart your terminal.

**Linux/macOS:**
Add to `~/.bashrc` or `~/.zshrc`:
```bash
export VCPKG_ROOT=/path/to/vcpkg
```

### 2. Clean Old Build Directories

```cmd
# Windows
clean.cmd

# Or manually
rmdir /S /Q build-debug
rmdir /S /Q build-release
rmdir /S /Q bin
```

### 3. Build with New System

```cmd
# Using presets (recommended)
cmake --preset debug
cmake --build --preset debug

# Or using convenience script
build-debug.cmd
```

## What's Still Supported?

### Legacy Scripts
The old build scripts still exist but are deprecated:
- `cpp-build.cmd` - Use `build-debug.cmd` instead
- `config_debug_build.cmd` - Use `cmake --preset debug` instead
- `config_release_build.cmd` - Use `cmake --preset release` instead

### Build Options
All existing CMake options are still supported:
- `BUILD_QT_EXAMPLES` (default: ON)
- `BUILD_VTK_EXAMPLES` (default: OFF)
- `BUILD_EIGEN_EXAMPLES` (default: ON)
- `BUILD_MIXED_LANG_EXAMPLES` (default: OFF)

### Output Directory
Executables still go to `bin/` directory as before.

## Troubleshooting

### "vcpkg not found" Error

**Solution 1:** Set VCPKG_ROOT environment variable (recommended)
```cmd
setx VCPKG_ROOT "E:\vcpkg"
```

**Solution 2:** Manually specify toolchain file
```cmd
cmake -B build-debug -DCMAKE_TOOLCHAIN_FILE=E:/vcpkg/scripts/buildsystems/vcpkg.cmake
```

### CMake Version Too Old

Upgrade to CMake 3.20 or higher:
- Download from: https://cmake.org/download/
- Or use: `winget install Kitware.CMake`

### Ninja Not Found

The presets use Ninja by default for faster builds. Install it:
```cmd
winget install Ninja-build.Ninja
```

Or use Visual Studio generator instead:
```cmd
cmake --preset vs2022
```

## IDE Integration

### Visual Studio Code
1. Install CMake Tools extension
2. Select a preset from the status bar
3. Click Build

### Visual Studio 2022
1. Open folder in Visual Studio
2. Select preset from Configuration dropdown
3. Build as normal

### CLion
1. CLion auto-detects CMake presets
2. Select preset from configuration dropdown
3. Build as normal

## Benefits of Migration

- ✅ Works with standard CMake commands
- ✅ Better IDE integration
- ✅ No hardcoded paths
- ✅ Cross-platform consistency
- ✅ Easier for new users
- ✅ Industry-standard approach
