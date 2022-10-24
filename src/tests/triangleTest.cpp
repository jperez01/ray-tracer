#include <gtest/gtest.h>

#include "primitives/ray.h"
#include "shapes/triangle.h"

TEST(triangleTest, initialTriangle) {
    Tuple p1 = Point(0, 1, 0);
    Tuple p2 = Point(-1, 0, 0);
    Tuple p3 = Point(1, 0, 0);

    Triangle t(p1, p2, p3);

    EXPECT_TRUE(t.normal() == Vector(0, 0, -1));
    EXPECT_TRUE(t.e1() == Vector(-1, -1, 0));
    EXPECT_TRUE(t.e2() == Vector(1, -1, 0));
}

TEST(triangleTest, parallelRay) {
    Tuple p1 = Point(0, 1, 0);
    Tuple p2 = Point(-1, 0, 0);
    Tuple p3 = Point(1, 0, 0);
    Triangle t(p1, p2, p3);

    Ray r(Point(0, -1, -2), Vector(0, 1, 0));

    Intersections results{};
    t.findIntersection(r, results);
    EXPECT_TRUE(results.size() == 0);
}

TEST(triangleTest, rayMissespEdges) {
    Tuple p1 = Point(0, 1, 0);
    Tuple p2 = Point(-1, 0, 0);
    Tuple p3 = Point(1, 0, 0);
    Triangle t(p1, p2, p3);

    Ray r(Point(1, 1, -2), Vector(0, 0, 1));

    Intersections results{};
    t.findIntersection(r, results);
    EXPECT_TRUE(results.size() == 0);

    Ray r2(Point(-1, 1, -2), Vector(0, 0, 1));
    t.findIntersection(r2, results);
    EXPECT_TRUE(results.size() == 0);

    Ray r3(Point(0, -1, -2), Vector(0, 0, 1));
    t.findIntersection(r3, results);
    EXPECT_TRUE(results.size() == 0);
}

TEST(triangleTest, rayHits) {
    Tuple p1 = Point(0, 1, 0);
    Tuple p2 = Point(-1, 0, 0);
    Tuple p3 = Point(1, 0, 0);
    Triangle t(p1, p2, p3);

    Ray r(Point(0, 0.5, -2), Vector(0, 0, 1));

    Intersections results{};
    t.findIntersection(r, results);
    EXPECT_TRUE(results.size() == 1);
    EXPECT_TRUE(results[0].m_time == 2.0);
}