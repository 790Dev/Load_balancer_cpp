cmake_minimum_required(VERSION 3.16)

project(
    Layer7LoadBalancer
    VERSION 1.0
    DESCRIPTION "Production Style Layer-7 HTTP Load Balancer"
    LANGUAGES CXX
)


# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Include Directory
include_directories(include)


# Source Files
set(SOURCES
    src/main.cpp
)

# Executable
add_executable(load_balancer ${SOURCES})