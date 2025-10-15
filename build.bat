@echo off
REM Simple CMake build script with MSVC or MinGW support

REM Usage:
REM   build.bat          -> Debug build (default generator)
REM   build.bat release  -> Release build
REM   build.bat msvc     -> Debug build using Visual Studio (MSVC)
REM   build.bat mingw    -> Debug build using MinGW
REM   build.bat clean    -> Clean build files
REM   build.bat clean-all -> Remove build + bin completely

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
    echo Removing entire build directory and binaries...
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
set GENERATOR=""

if "%1"=="release" (
    set BUILD_TYPE=Release
)

if "%1"=="msvc" (
    set GENERATOR=-G "Visual Studio 17 2022"
)
if "%1"=="mingw" (
    set GENERATOR=-G "MinGW Makefiles"
)

if not exist build mkdir build

echo Configuring project with CMake for %BUILD_TYPE%...
cmake %GENERATOR% -S . -B build -DCMAKE_BUILD_TYPE=%BUILD_TYPE%

if errorlevel 1 (
    echo [ERROR] CMake configuration failed!
    pause
    exit /b
)

echo Building project...
cmake --build build --config %BUILD_TYPE%

echo Build complete.
pause
