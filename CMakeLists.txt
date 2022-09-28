cmake_minimum_required(VERSION 3.22)
project(rayTracer VERSION 1.0.0)
include(FetchContent)
set(CMAKE_CXX_STANDARD 17)

enable_testing()
find_package(GTest REQUIRED)
set(CMAKE_OSX_ARCHITECTURES "arm64")

add_library(
    primitives
    src/primitives/color.cpp
    src/primitives/math.h
    src/primitives/tuple.cpp
    src/primitives/intersection.cpp
    src/primitives/intersections.cpp
    src/primitives/ray.cpp
    src/primitives/matrix.cpp
)
target_include_directories(primitives PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_library(
    display
    src/display/canvas.cpp
)
target_include_directories(display PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_library(
    shapes
    src/shapes/material.cpp
    src/shapes/shape.h
    src/shapes/sphere.cpp
)
target_include_directories(shapes PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_library(
    images
    src/images/pmm_writer.cpp
)
target_include_directories(images PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_library(
    lights
    src/lights/point_light.cpp
    src/lights/direction_light.cpp
)
target_include_directories(lights PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_executable(imageWriter ./src/main.cpp)
target_link_libraries(imageWriter GTest::gtest GTest::gtest_main pthread primitives display shapes images lights)
