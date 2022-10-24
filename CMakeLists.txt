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
    src/shapes/shape.cpp
    src/shapes/sphere.cpp
    src/shapes/plane.cpp
    src/shapes/cube.cpp
    src/shapes/cylinder.cpp
    src/shapes/group.cpp
    src/shapes/bounds.cpp
    src/shapes/triangle.cpp
    src/shapes/smooth_triangle.cpp
)
target_include_directories(shapes PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(shapes primitives)

add_library(
    images
    src/images/pmm_writer.cpp
)
target_include_directories(images PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_library(
    scene
    src/scene/world.cpp
    src/scene/computations.cpp
    src/scene/camera.cpp
)
target_include_directories(scene PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_library(
    lights
    src/lights/point_light.cpp
    src/lights/direction_light.cpp
)
target_include_directories(lights PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_library(
    extras
    src/extras/obj_parser.cpp
)
target_include_directories(extras PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_library(
    patterns
    src/patterns/pattern.h
    src/patterns/striped_pattern.cpp
    src/patterns/gradient_pattern.cpp
    src/patterns/ring_pattern.cpp
)
target_include_directories(patterns PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_executable(mainWriter ./src/main.cpp)
target_link_libraries(mainWriter GTest::gtest GTest::gtest_main pthread 
    primitives display shapes images lights scene patterns extras)

add_executable(
    tests
    src/tests/sceneTest.cpp
    src/tests/lightingTest.cpp
    src/tests/shadowTest.cpp
    src/tests/patternTest.cpp
    src/tests/reflectTest.cpp
    src/tests/cubeTest.cpp
    src/tests/cylinderTest.cpp
    src/tests/triangleTest.cpp)
target_include_directories(tests PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(tests GTest::gtest GTest::gtest_main pthread
    primitives display shapes images lights scene patterns)
