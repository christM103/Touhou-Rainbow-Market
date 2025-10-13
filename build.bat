@echo off
REM Simple CMake build script

if "%1"=="clean" (
    echo Running CMake clean...
    if exist build (
        cmake --build build --target clean
    ) else (
        echo No build directory found.
    )
    exit /b
)

if "%1"=="clean-all" (
    echo Removing entire build directory...
    rmdir /s /q build
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
cmake -S . -B build -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
cmake --build build --config %BUILD_TYPE%

pause