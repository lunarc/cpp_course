@echo off
REM Clean all build directories

echo Cleaning build directories...

if exist build-debug (
    echo Removing build-debug...
    rmdir /S /Q build-debug
)

if exist build-release (
    echo Removing build-release...
    rmdir /S /Q build-release
)

if exist build-default (
    echo Removing build-default...
    rmdir /S /Q build-default
)

if exist build-vs2022 (
    echo Removing build-vs2022...
    rmdir /S /Q build-vs2022
)

if exist bin (
    echo Removing bin...
    rmdir /S /Q bin
)

echo.
echo Clean completed!
