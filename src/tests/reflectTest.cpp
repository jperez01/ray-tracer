#include <gtest/gtest.h>
#include "shapes/material.h"
#include "primitives/math.h"
#include "shapes/plane.h"
#include "scene/computations.h"

#include "lights/point_light.h"
#include "shapes/sphere.h"
#include "shapes/plane.h"
#include "scene/world.h"

#include <cmath>

TEST(reflectTest, defaultReflection) {
    Material material{};
    EXPECT_TRUE(epsilon_eq(0.0, material.reflective()));
}

TEST(reflectTest, computeReflectVector) {
    Plane plane{};

    Tuple point = Point(0, 1, -1);
    Tuple vector = Vector(0, -sqrt(2)/2, sqrt(2)/2);
    Ray ray(point, vector);

    Intersection i(sqrt(2), &plane);

    Computations computations(i, ray);

    EXPECT_TRUE(Vector(0, sqrt(2)/2, sqrt(2)/2) == computations.reflectv());
}

TEST(reflectTest, limitRecursion) {
    Tuple origin = Point(-10, 10, -10);
    Color color(1, 1, 1);
    PointLight light(color, origin);

    Material material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200.0);
    Sphere s1 = Sphere(material);

    origin = Point(0, 0, 0);
    Material material2{};
    Matrix transform = scaleMatrix(0.5, 0.5, 0.5);
    Sphere s2 = Sphere(origin, 1.0, material2, transform);

    Material material3{};
    Tuple normal = Vector(0, 1, 0);
    material3.setReflective(0.5);
    transform = translationMatrix(0, -1, 0);
    Plane p(origin, normal, transform, material3);


    std::vector<Shape *> shapes;
    shapes.push_back(&s1);
    shapes.push_back(&s2);
    shapes.push_back(&p);

    std::vector<PointLight> pointLights;
    pointLights.push_back(light);

    World defaultWorld(shapes, pointLights);

    Ray r(Point(0, 0, -3), Vector(0, -sqrt(2)/2, sqrt(2)/2));
    Intersection i(sqrt(2), &p);

    Computations comps(i, r);

    Color result = defaultWorld.findReflection(comps, 0);

    EXPECT_TRUE(result == Color(0, 0, 0));
}

