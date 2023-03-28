add_library(primitives
    primitives/newPrimitives.cpp
    primitives/color.cpp
    primitives/math.h
    primitives/intersections.cpp
    primitives/ray.cpp)

target_include_directories(primitives PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(primitives glm)