#!/bin/bash
# Simple CMake build script

# CMake clean
if [ "$1" == "clean" ]; then
    echo "Running CMake clean..."
    if [ -d "build" ]; then
        cmake --build build --target clean
    else
        echo "No build directory found."
    fi
    exit 0
fi

# Full clean: remove build and bin directories
if [ "$1" == "clean-all" ]; then
    echo "Removing entire build directory..."
    rm -rf build
    rm -rf bin
    echo "Full clean complete."
    exit 0
fi

# Linting target
if [ "$1" == "lint" ]; then
    echo "Running linting..."
    cmake --build build --target lint
    exit 0
fi

# Default build type is Debug
BUILD_TYPE="Debug"

# Switch to Release if specified
if [ "$1" == "release" ]; then
    BUILD_TYPE="Release"
fi

# Create build directory if it doesn't exist and build the project
mkdir -p build
cmake -S . -B build -DCMAKE_BUILD_TYPE=$BUILD_TYPE
cmake --build build -j$(nproc)
