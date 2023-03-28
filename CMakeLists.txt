cmake_minimum_required(VERSION 3.22)
project(rayTracer VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

option(gtest_disable_pthreads "Disable uses of pthreads in gtest." ON)

enable_testing()

set(CMAKE_OSX_ARCHITECTURES "arm64")

add_subdirectory(third_party)
add_subdirectory(src)

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
    src/shapes/constructive_solid_geometry.cpp
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
target_link_libraries(scene primitives)

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
target_link_libraries(mainWriter glm
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
target_link_libraries(tests GTest::gtest GTest::gtest_main 
    primitives display shapes images lights scene patterns)

include(GoogleTest)
gtest_discover_tests(tests)
