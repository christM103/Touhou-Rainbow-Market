#!/bin/bash
# Simple CMake build script

if [ "$1" == "clean" ]; then
    echo "Running CMake clean..."
    if [ -d "build" ]; then
        cmake --build build --target clean
    else
        echo "No build directory found."
    fi
    exit 0
fi

if [ "$1" == "clean-all" ]; then
    echo "Removing entire build directory..."
    rm -rf build
    echo "Full clean complete."
    exit 0
fi

if [ "$1" == "lint" ]; then
    echo "Running linting..."
    cmake --build build --target lint
    exit 0
fi


BUILD_TYPE="Debug"
if [ "$1" == "release" ]; then
    BUILD_TYPE="Release"
fi

mkdir -p build
cmake -S . -B build -DCMAKE_BUILD_TYPE=$BUILD_TYPE
cmake --build build -j$(nproc)
