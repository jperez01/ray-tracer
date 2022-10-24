#include <gtest/gtest.h>
#include "shapes/sphere.h"
#include "primitives/math.h"
#include "lights/point_light.h"
#include <cmath>

TEST(lightingTest, sphereNormals) {
    Intersection i{0.0};
    Sphere first{};
    Tuple firstPoint = Point(1, 0, 0);
    Tuple result = first.surfaceNormal(firstPoint, i);

    EXPECT_FLOAT_EQ(result.x, 1.0);
    EXPECT_FLOAT_EQ(result.y, 0.0);
    EXPECT_FLOAT_EQ(result.z, 0.0);

    Sphere second{};
    Tuple secondPoint = Point(0, 1, 0);
    result = second.surfaceNormal(secondPoint, i);

    EXPECT_FLOAT_EQ(result.x, 0.0);
    EXPECT_FLOAT_EQ(result.y, 1.0);
    EXPECT_FLOAT_EQ(result.z, 0.0);

    Sphere third{};
    Tuple thirdPoint = Point(0, 0, 1);
    result = third.surfaceNormal(thirdPoint, i);

    EXPECT_FLOAT_EQ(result.x, 0.0);
    EXPECT_FLOAT_EQ(result.y, 0.0);
    EXPECT_FLOAT_EQ(result.z, 1.0);
}

TEST(lightingTest, transformedNormals) {
    Intersection i{0.0};
    Sphere first{};
    Matrix firstTransform = translationMatrix(0, 1, 0);
    first.setTransform(firstTransform);

    Tuple firstPoint = Point(0, 1.70711, -0.70711);
    Tuple firstResult = first.surfaceNormal(firstPoint, i);

    EXPECT_TRUE(epsilon_eq(firstResult.x, 0));
    EXPECT_TRUE(epsilon_eq(firstResult.y, 0.70711));
    EXPECT_TRUE(epsilon_eq(firstResult.z, -0.70711));

    Sphere second{};
    Matrix secondTransform = scaleMatrix(1, 0.5, 1) * rotationZ(M_PI / 5);
    second.setTransform(secondTransform);

    Tuple secondPoint = Point(0, sqrt(2) / 2, -sqrt(2) / 2);
    Tuple secondResult = second.surfaceNormal(secondPoint, i);

    EXPECT_TRUE(epsilon_eq(secondResult.x, 0));
    EXPECT_TRUE(epsilon_eq(secondResult.y, 0.97014));
    EXPECT_TRUE(epsilon_eq(secondResult.z, -0.24254));
}

TEST(lightingTest, reflectingVector) {
    Tuple vector = Vector(1, -1, 0);
    Tuple normal = Vector(0, 1, 0);
    Tuple result = reflect(vector, normal);
    EXPECT_TRUE(result == Vector(1, 1, 0));

    vector = Vector(0, -1, 0);
    normal = Vector(sqrt(2) / 2, sqrt(2) / 2, 0);
    result = reflect(vector, normal);
    EXPECT_TRUE(result == Vector(1, 0, 0));
}

TEST(lightingTest, defaultMaterial) {
    Material material{};

    EXPECT_TRUE(material.color() == Color(1, 1, 1));
    EXPECT_TRUE(epsilon_eq(material.ambient(), 0.1));
    EXPECT_TRUE(epsilon_eq(material.specular(), 0.9));
    EXPECT_TRUE(epsilon_eq(material.diffuse(), 0.9));
    EXPECT_TRUE(epsilon_eq(material.shininess(), 200.0));
}

TEST(lightingTest, simpleSphere) {
    Sphere simpleSphere{};
    Material defaultMaterial{};

    Material result = simpleSphere.material();

    EXPECT_TRUE(defaultMaterial == result);
}

TEST(lightingTest, simpleLighting) {
    Material material{};
    Tuple position = Point(0, 0, 0);

    Tuple eye = Vector(0, 0, -1);
    Tuple normal = Vector(0, 0, -1);
    PointLight light(Color(1, 1, 1), Point(0, 0, -10));

    Color result = calculateColorFromPoint(light, normal, position, eye, material);
    EXPECT_TRUE(result == Color(1.9, 1.9, 1.9));

    eye = Vector(0, sqrt(2) / 2, sqrt(2) / 2);
    result = calculateColorFromPoint(light, normal, position, eye, material);
    EXPECT_TRUE(result == Color(1.0, 1.0, 1.0));

    eye = Vector(0, 0, -1);
    light = PointLight(Color(1, 1, 1), Point(0, 10, -10));
    result = calculateColorFromPoint(light, normal, position, eye, material);
    EXPECT_TRUE(result == Color(0.7364, 0.7364, 0.7364));

    eye = Vector(0, -sqrt(2) / 2, -sqrt(2) / 2);
    light = PointLight(Color(1, 1, 1), Point(0, 10, -10));
    result = calculateColorFromPoint(light, normal, position, eye, material);
    EXPECT_TRUE(result == Color(1.6364, 1.6364, 1.6364));
}