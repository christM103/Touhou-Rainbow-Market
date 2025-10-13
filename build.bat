@echo off
REM Simple CMake build script

if "%1"=="clean" (
    echo Running CMake clean...
    if exist build (
        cmake --build build --target clean
    ) else (
        echo No build directory found.
    )
    if exist bin (
        del /q bin\*.exe >nul 2>&1
    )
    exit /b
)

if "%1"=="clean-all" (
    echo Removing entire build directory...
    rmdir /s /q build
    rmdir /s /q bin
    echo Full clean complete.
    exit /b
)

if "%1"=="lint" (
    echo Running cpplint on all source files...
    cmake --build build --target lint
    echo Linting complete.
    exit /b
)

set BUILD_TYPE=Debug
if "%1"=="release" (
    set BUILD_TYPE=Release
)

if not exist build mkdir build

echo Configuring project with CMake for %BUILD_TYPE%...
cmake -G "MinGW Makefiles" -S . -B build -DCMAKE_BUILD_TYPE=%BUILD_TYPE%

if errorlevel 1 (
    echo [ERROR] CMake configuration failed!
    pause
    exit /b
)

echo Building project...
cmake --build build --config %BUILD_TYPE%

echo Build complete.