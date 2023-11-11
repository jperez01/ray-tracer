find_package(glog CONFIG REQUIRED)
message("${glog_DIR}")

add_library(core
    core/pbrt.h
    core/geometry.h
    core/geometry.cpp
    core/stats.h
    core/stats.cpp
    core/parallel.h
    core/parallel.cpp
    core/progressreporter.h
    core/progressreporter.cpp
    core/quaternion.h
    core/quaternion.cpp
    core/transform.h
    core/transform.cpp
    core/interaction.h
    core/interaction.cpp
    core/medium.cpp
    core/spectrum.cpp
    core/material.cpp
    core/sampler.cpp
    core/stringprint.h)
target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include)

add_library(primitives
    primitives/color.cpp
    primitives/matrix.cpp
    primitives/tuple.cpp
    primitives/intersections.cpp
    primitives/ray.cpp)
target_include_directories(primitives PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

add_library(
    shapes

    shapes/shape.cpp
    shapes/sphere.cpp
    shapes/triangle.cpp
    shapes/bounds.cpp
)
target_include_directories(shapes PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/include)

add_library(materials
    materials/material.cpp)
target_include_directories(materials PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include)

add_library(
    display
    display/canvas.cpp
)
target_include_directories(display PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/include)

add_library(
    images
    images/pmm_writer.cpp
)
target_include_directories(images PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/include)

add_library(
    scene
    scene/world.cpp
    scene/computations.cpp
    scene/camera.cpp
)
target_include_directories(scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/include)

add_library(
    lights
    lights/point_light.cpp
    lights/direction_light.cpp
)
target_include_directories(lights PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/include)


add_library(
    patterns
    patterns/pattern.h
    patterns/striped_pattern.cpp
    patterns/gradient_pattern.cpp
    patterns/ring_pattern.cpp
)
target_include_directories(patterns PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/include)

add_library(
    samplers
    samplers/stratified.cpp
)
target_include_directories(samplers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/include)

add_library(
    filters
    filters/allFilters.cpp)
target_include_directories(filters PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/include)

target_link_libraries(shapes materials primitives)
target_link_libraries(scene lights)

add_executable(mainWriter ./main.cpp)
target_link_libraries(mainWriter glog::glog primitives core filters samplers materials display 
  shapes images lights scene patterns stb_image)