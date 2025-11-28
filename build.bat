@echo off
REM ===============================================
REM Simple CMake build script for TouhouRainbowMarket
REM Supports MSVC, MinGW, Debug/Release, cleaning, and SDL2 setup
REM ===============================================

setlocal enabledelayedexpansion

REM ---- Handle cleaning ----
if "%1"=="clean" (
    echo [INFO] Cleaning build directory...
    if exist build (
        cmake --build build --target clean
    ) else (
        echo [WARN] No build directory found.
    )
    if exist bin del /q bin\*.exe >nul 2>&1
    exit /b
)

if "%1"=="clean-all" (
    echo [INFO] Removing build/, bin/, and lib/...
    rmdir /s /q build 2>nul
    rmdir /s /q bin 2>nul
    rmdir /s /q lib 2>nul
    echo [DONE] Full clean complete.
    exit /b
)

if "%1"=="lint" (
    echo [INFO] Running cpplint on all source files...
    cmake --build build --target lint
    echo [DONE] Linting complete.
    exit /b
)

REM ---- Default values ----
set "BUILD_TYPE=Debug"
set "GENERATOR="
set "TARGET="

REM ---- Parse arguments ----
for %%A in (%*) do (
    if /I "%%A"=="release" set "BUILD_TYPE=Release"
    if /I "%%A"=="debug" set "BUILD_TYPE=Debug"
    if /I "%%A"=="msvc" set "GENERATOR=Visual Studio 17 2022"
    if /I "%%A"=="mingw" set "GENERATOR=MinGW Makefiles"
    if /I "%%A"=="trm" set "TARGET=--target TRM"
)

REM ---- Auto-detect compiler if not specified ----
if "%GENERATOR%"=="" (
    where cl >nul 2>nul
    if %errorlevel%==0 (
        set "GENERATOR=Visual Studio 17 2022"
        echo [INFO] Detected MSVC.
    ) else (
        where gcc >nul 2>nul
        if %errorlevel%==0 (
            set "GENERATOR=MinGW Makefiles"
            echo [INFO] Detected MinGW.
        ) else (
            echo [ERROR] Could not detect MSVC or MinGW! Please specify one.
            exit /b 1
        )
    )
)

REM ---- Create build folder if missing ----
if not exist build mkdir build

REM ---- Configure project ----
echo [INFO] Configuring project (%BUILD_TYPE%) with %GENERATOR%...
cmake -G "%GENERATOR%" -S . -B build -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
    -DSDL2_DIR="%SDL2_DIR%" ^
    -DSDL2_image_DIR="%SDL2_image_DIR%" ^
    -DSDL2_ttf_DIR="%SDL2_ttf_DIR%"

if errorlevel 1 (
    echo [ERROR] CMake configuration failed!
    pause
    exit /b 1
)

REM ---- Build ----
echo [INFO] Building project...
cmake --build build --config %BUILD_TYPE% %TARGET%

if errorlevel 1 (
    echo [ERROR] Build failed!
    pause
    exit /b 1
)

echo [SUCCESS] Build complete!
exit /b 0
