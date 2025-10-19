# CMake configuration for C++ game project using SDL2
cmake_minimum_required(VERSION 3.10)
project("TouhouRainbowMarket" LANGUAGES CXX)

# Set build type to Release by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# Source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Create executable
add_executable(TRM ${SRC_FILES})

target_include_directories(TRM PRIVATE ${CMAKE_SOURCE_DIR}/include)

# SDL setup (cross-platform)
if(WIN32)
    if(MSVC)
        message(STATUS "Using MSVC toolchain")
        # On Windows, use the SDL folder you included (Visual Studio 64-bit)
        set(SDL2_DIR ${CMAKE_SOURCE_DIR}/SDL2/SDL2-devel-2.32.8-VC/SDL2-2.32.8)
        set(SDL2_ttf_DIR ${CMAKE_SOURCE_DIR}/SDL2/SDL2_ttf-devel-2.24.0-VC/SDL2_ttf-2.24.0)
        set(SDL2_image_DIR ${CMAKE_SOURCE_DIR}/SDL2/SDL2_image-devel-2.8.6-VC/SDL2_image-2.8.6)

        # Include SDL2 headers
        target_include_directories(TRM PRIVATE
            ${SDL2_DIR}/include
            ${SDL2_DIR}/include/SDL2
            ${SDL2_ttf_DIR}/include
            ${SDL2_image_DIR}/include
        )

        # Link SDL2 libraries
        target_link_directories(TRM PRIVATE
            ${SDL2_DIR}/lib/x64
            ${SDL2_ttf_DIR}/lib/x64
            ${SDL2_image_DIR}/lib/x64
        )

        # Link against SDL2 libraries
        target_link_libraries(TRM PRIVATE SDL2main SDL2 SDL2_ttf SDL2_image)

        # Copy SDL2.dll automatically to bin/
        add_custom_command(TARGET TRM POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SDL2_DIR}/lib/x64/SDL2.dll"
                "${SDL2_ttf_DIR}/lib/x64/SDL2_ttf.dll"
                "${SDL2_image_DIR}/lib/x64/SDL2_image.dll"
                "$<TARGET_FILE_DIR:TRM>/"
        )

    else ()
        message(STATUS "Using MinGW toolchain")
        # On Windows, use the SDL folder you included (minGW-w64 64-bit)
        set(SDL2_DIR ${CMAKE_SOURCE_DIR}/SDL2/SDL2-devel-2.32.8-mingw/SDL2-2.32.8/x86_64-w64-mingw32)
        set(SDL2_ttf_DIR ${CMAKE_SOURCE_DIR}/SDL2/SDL2_ttf-devel-2.24.0-mingw/SDL2_ttf-2.24.0/x86_64-w64-mingw32)
        set(SDL2_image_DIR ${CMAKE_SOURCE_DIR}/SDL2/SDL2_image-devel-2.8.6-mingw/SDL2_image-2.8.6/x86_64-w64-mingw32)

        # Include SDL2 headers
        target_include_directories(TRM PRIVATE
            ${SDL2_DIR}/include
            ${SDL2_DIR}/include/SDL2
            ${SDL2_ttf_DIR}/include
            ${SDL2_image_DIR}/include
        )

        # Link SDL2 libraries
        target_link_directories(TRM PRIVATE
            ${SDL2_DIR}/lib
            ${SDL2_ttf_DIR}/lib
            ${SDL2_image_DIR}/lib
        )

        # Link against SDL2 libraries
        target_link_libraries(TRM PRIVATE mingw32 SDL2main SDL2 SDL2_ttf SDL2_image)

        # Copy SDL2.dll automatically to bin/
        add_custom_command(TARGET TRM POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SDL2_DIR}/bin/SDL2.dll"
                "${SDL2_ttf_DIR}/bin/SDL2_ttf.dll"
                "${SDL2_image_DIR}/bin/SDL2_image.dll"
                "$<TARGET_FILE_DIR:TRM>/"
        )

    endif()

else()
    # On Linux rely on system-installed SDL2
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(TRM PRIVATE ${SDL2_LIBRARIES})
endif()

# Copy assets automatically
add_custom_command(TARGET TRM POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:TRM>/assets
)

# Linting target using cpplint
add_custom_target(lint
    COMMAND ${CMAKE_COMMAND} -E echo "Running cpplint..."
    COMMAND cpplint --recursive src include
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)