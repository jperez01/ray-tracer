#include <gtest/gtest.h>

#include "primitives/ray.h"
#include "shapes/cylinder.h"

TEST(cylinderTest, rayMisses) {
    Tuple origin = Point(1, 0, 0);
    Tuple direction = Vector(0, 1, 0);
    direction = direction.normalized();
    Ray r(origin, direction);

    Cylinder c{};
    Intersections results{};
    c.findIntersection(r, results);

    std::vector<Intersection> results_vector = results.intersectionsList();
    EXPECT_TRUE(results.size() == 0);
}

TEST(cylinderTest, rayHits) {
    Tuple origin = Point(1, 0, -5);
    Tuple direction = Vector(0, 0, 1);
    direction = direction.normalized();
    Ray r(origin, direction);

    Cylinder c{};
    Intersections results{};
    c.findIntersection(r, results);

    std::vector<Intersection> results_vector = results.intersectionsList();
    EXPECT_TRUE(results[0] == 5);
    EXPECT_TRUE(results[1] == 5);
}

TEST(cylinderTest, surfaceNormal) {
    Cylinder c{};
    Tuple point = Point(0, 5, -1);

    Tuple result = c.surfaceNormal(point);
    EXPECT_TRUE(result == Vector(0, 0, -1));
}

TEST(cylinderTest, truncatedCylinder) {
    Cylinder c(1, 2);

    Tuple origin = Point(0, 1.5, 0);
    Tuple direction = Vector(0.1, 1, 0);
    direction = direction.normalized();
    Ray r(origin, direction);

    Intersections results{};
    c.findIntersection(r, results);

    std::vector<Intersection> results_vector = results.intersectionsList();
    EXPECT_TRUE(results.size() == 0);
}