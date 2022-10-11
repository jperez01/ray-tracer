#include <gtest/gtest.h>

#include "shapes/cube.h"
#include "primitives/ray.h"

TEST(cubeTest, rayIntersectsCube) {
    Cube c{};

    Tuple origin = Point(5, 0.5, 0);
    Tuple direction = Vector(-1, 0, 0);
    Ray r(origin, direction);

    Intersections results{};
    c.findIntersection(r, results);

    std::vector<Intersection> results_vector = results.intersectionsList();
    EXPECT_TRUE(results[0].m_time == 4);
    EXPECT_TRUE(results[1].m_time == 6);
}

TEST(cubeTest, rayMissesCube) {
    Cube c{};

    Tuple origin = Point(-2, 0, 0);
    Tuple direction = Vector(0.2673, 0.5345, 0.8018);
    Ray r(origin, direction);

    Intersections results{};
    c.findIntersection(r, results);
    EXPECT_TRUE(results.size() == 0);
}

TEST(cubeTest, cubeNormal) {
    Cube c{};
    Tuple point = Point(1, 0.5, -0.8);
    Tuple normal = c.surfaceNormal(point);

    EXPECT_TRUE(normal == Vector(1, 0, 0));
}