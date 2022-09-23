#include <iostream>
#include <gtest/gtest.h>
#include "shapes/sphere.h"
#include "primitives/intersection.h"
#include "primitives/ray.h"
#include "primitives/intersections.h"
#include "primitives/tuple.h"

TEST(SphereTest, DoesIntersect) {
    Tuple center = Point(0.0, 0.0, 0.0);
    Sphere sphere = Sphere(center, 1.0);

    Tuple origin = Point(0.0, 0.0, 0.0);
    Tuple direction = Vector(0.0, 0.0, 1.0);
    Ray ray = Ray(origin, direction);

    Intersections results = sphere.findIntersection(ray);
    std::optional<Intersection> result = results.hit();
    
    EXPECT_TRUE(result.has_value());
}

TEST(SphereTest, DoesntIntersect) {
    Tuple center = Point(10.0, 0.0, 0.0);
    Sphere sphere = Sphere(center, 1.0);

    Tuple origin = Point(0.0, 0.0, 0.0);
    Tuple direction = Vector(0.0, 0.0, 1.0);
    Ray ray = Ray(origin, direction);

    Intersections results = sphere.findIntersection(ray);
    std::optional<Intersection> result = results.hit();
    
    EXPECT_FALSE(result.has_value());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}