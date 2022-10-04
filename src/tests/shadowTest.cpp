#include <gtest/gtest.h>
#include "primitives/tuple.h"
#include "lights/point_light.h"
#include "scene/world.h"
#include "shapes/sphere.h"

TEST(shadowTest, lightInShadow) {
    Tuple eye = Vector(0, 0, -1);
    Tuple normal = Vector(0, 0, -1);
    Tuple position = Point(0, 0, 0);
    Material material{};

    PointLight light(Color(1, 1, 1), Point(0, 0, -10));
    Color result = calculateColorFromPoint(light, normal, position, eye, material, true);
    EXPECT_TRUE(result == Color(0.1, 0.1, 0.1));
}

TEST(shadowTest, isInShadow) {
        Tuple origin = Point(-10, 10, -10);
    Color color(1, 1, 1);
    PointLight light(color, origin);

    Material material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200.0);
    Sphere s1 = Sphere(material);

    origin = Point(0, 0, 0);
    Material material2{};
    Matrix transform = scaleMatrix(0.5, 0.5, 0.5);
    Sphere s2 = Sphere(origin, 1.0, material2, transform);

    std::vector<Shape *> shapes;
    shapes.push_back(&s1);
    shapes.push_back(&s2);

    std::vector<PointLight> pointLights;
    pointLights.push_back(light);

    World defaultWorld(shapes, pointLights);

    Tuple point = Point(10, -10, 10);
    bool result = defaultWorld.isShadowed(point, light);
    EXPECT_TRUE(result);

    point = Point(-20, 20, -20);
    result = defaultWorld.isShadowed(point, light);
    EXPECT_FALSE(result);

    point = Point(-2, 2, -2);
    result = defaultWorld.isShadowed(point, light);
    EXPECT_FALSE(result);
}

TEST(shadowTest, offsetPoint) {
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere shape{};
    Matrix transform = translationMatrix(0, 0, 1);
    shape.setTransform(transform);

    Intersection i(5.00, &shape);
    Computations results(i, ray);

    Tuple overPoint = results.overPoint();
    Tuple point = results.point();
    EXPECT_TRUE(overPoint.z < -0.01/2 && point.z > overPoint.z);
}