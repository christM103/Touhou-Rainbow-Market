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
file(GLOB SRC_FILES src/*.cpp)

# Create executable
add_executable(TRM ${SRC_FILES})

# SDL setup (cross-platform)
if(WIN32)
    # On Windows, use the SDL folder you included
    set(SDL2_DIR ${CMAKE_SOURCE_DIR}/SDL)
    target_include_directories(TRM PRIVATE ${SDL2_DIR}/include)
    target_link_directories(TRM PRIVATE ${SDL2_DIR}/lib)
    target_link_libraries(TRM PRIVATE SDL2main SDL2)

    # Copy SDL2.dll automatically to bin/
    add_custom_command(TARGET TRM POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_DIR}/lib/SDL2.dll"
            "$<TARGET_FILE_DIR:TRM>/SDL2.dll"
    )
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