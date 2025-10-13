# Touhou Rainbow Market
A cross-platform C++ fan game inspired by the Touhou Project, built with **SDL2** and **CMake**. This repository contains the full source code, assets, and build scripts needed to compile and run the project.

**This project is in active development.** Gameplay, features, and systems are not yet finalized.

---

## Table of Contents
* [Features](#features)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Building the Project](#building-the-project)
* [How to Run](#️how-to-run)
* [Authors](#authors)
* [license](#license)

---

## Features
* Cross-platform build system supporting Windows and Linux.
* Graphics and windowing powered by the **SDL2** library.
* Asset management for easy integration of sprites, fonts, and sounds.
* Automated build scripts for simple, one-command compilation.

---

## Getting Started
Follow these steps to compile the project on your local machine.

### Prerequisites

#### Windows
* [**CMake**](https://cmake.org/download/) (version 3.10 or newer)
* [**MinGW-w64**](https://www.mingw-w64.org/) (or another GCC-compatible C++ compiler)
* (Optional) **Visual Studio Code** with the *C/C++* and *CMake Tools* extensions.

    All SDL2 dependencies for Windows are included in this repository. No separate installation is needed.

#### Linux
You'll need a C++ compiler, CMake, and the SDL2 development libraries. On Debian/Ubuntu-based systems, you can install them with:
```bash
sudo apt update
sudo apt install build-essential cmake libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```

---

### Building the Project
The project uses CMake and a helper batch script.

#### Windows
On Windows you can use the 'build.bat' helper.
```
# Debug build (default)
.\build.bat

# Release build
.\build.bat release

# Clean build artifacts
.\build.bat clean

# Remove build and bin completely
.\build.bat clean-all
```

#### Linux

On Linux you can use the `build.sh` helper.
```
# Debug build (default)
./build.sh

# Release build
./build.sh release

# Clean build artifacts
./build.sh clean

# Remove build and bin completely
./build.sh clean-all
```

---

## How to Run
Once the project is built successfully, the final executable and all necessary assets and DLLs will be placed in the bin/ directory.

On Windows, you can either:

Double-click TRM.exe inside the bin/ folder.

Run it from the terminal: .\bin\TRM.exe

On Linux, run the following command from the project's root directory:
./bin/TRM

---

## Authors

Touhou Rainbow Team
* [Mango182](https://github.com/Mango182)
* [Chrisfantasy](https://github.com/christM103)
* Keymaster

---

## License
This project is licensed under the MIT License - see the LICENSE.md file for details.