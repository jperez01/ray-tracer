#include <gtest/gtest.h>
#include <cmath>
#include "primitives/math.h"

#include "scene/world.h"
#include "scene/camera.h"
#include "shapes/sphere.h"

World default_world() {
    Tuple origin = Point(-10, 10, -10);
    Color color(1, 1, 1);
    PointLight light(color, origin);

    Material material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 1.0);
    Sphere s1 = Sphere(material);

    origin = Point(0, 0, 0);
    Material material2{};
    Sphere s2 = Sphere(origin, 0.5, material2);

    std::vector<Shape *> shapes;
    shapes.push_back(&s1);
    shapes.push_back(&s2);

    std::vector<PointLight> pointLights;
    pointLights.push_back(light);

    return World(shapes, pointLights);
}

TEST(SceneTest, creation) {
    World world{};
    EXPECT_EQ(world.objects().size(), 0);
}

TEST(SceneTest, defaultWorld) {
    Tuple position(1.0, 1.0, 1.0);
    Color color(1.0, 1.0, 1.0);
    PointLight light(color, position);
    std::vector<PointLight> pointLights;
    pointLights.push_back(light);

    std::vector<Shape *> shapes;
    std::vector<DirectionalLight> directLights;

    World world(shapes, directLights, pointLights);

    EXPECT_EQ(world.pointLights().size() , 1);
}

TEST(SceneTest, intersectDefault) {
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

    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    Intersections result = defaultWorld.intersect(ray);

    float results[4] = {
        4, 4.5, 5.5, 6
    };

    for (int i = 0; i < result.size(); i++) {
        EXPECT_FLOAT_EQ(result[i].m_time, results[i]);
    }
}

TEST(SceneTest, simpleComputation) {
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere shape{};
    Intersection i(4, &shape, ray);
    Computations computations(i, ray);

    EXPECT_FLOAT_EQ(computations.time(), i.m_time);
    EXPECT_TRUE(computations.eye() == Vector(0, 0, -1));
    EXPECT_TRUE(computations.point() == Point(0, 0, -1));
    EXPECT_TRUE(computations.normal() == Vector(0, 0, -1));

    ray = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    i = Intersection(1, &shape, ray);
    computations = Computations(i, ray);

    EXPECT_FLOAT_EQ(computations.time(), i.m_time);
    EXPECT_TRUE(computations.eye() == Vector(0, 0, -1));
    EXPECT_TRUE(computations.point() == Point(0, 0, 1));
    EXPECT_TRUE(computations.normal() == Vector(0, 0, -1));
    EXPECT_TRUE(computations.isInside());
}

TEST(SceneTest, simpleShading) {
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

    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
    Intersection i(4, &s1, ray);
    Computations computations(i, ray);

    Color result = defaultWorld.shadeHit(computations);
    EXPECT_TRUE(result == Color(0.38066, 0.47583, 0.2855));

    std::vector<PointLight> newPointLights;
    PointLight newLight(Color(1, 1, 1), Point(0, 0.25, 0));
    newPointLights.push_back(newLight);
    defaultWorld.setPointLights(newPointLights);

    ray = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    Intersections results{};
    s2.findIntersection(ray, results);
    i = results.hit();
    i = Intersection(0.5, &s2);
    computations = Computations(i, ray);

    result = defaultWorld.shadeHit(computations);
    EXPECT_TRUE(result == Color(0.90498, 0.90498, 0.90498));
}

TEST(SceneTest, simpleViewTransform) {
    Tuple from = Point(1, 3, 2);
    Tuple to = Point(4, -2, 8);
    Tuple up = Vector(1, 1, 0);

    Matrix view = viewTransform(from, to, up);
    EXPECT_TRUE(epsilon_eq(view(0, 0), -0.50709));
    EXPECT_TRUE(epsilon_eq(view(0, 1), 0.50709));
    EXPECT_TRUE(epsilon_eq(view(0, 2), 0.67612));
    EXPECT_TRUE(epsilon_eq(view(0, 3), -2.36643));

    EXPECT_TRUE(epsilon_eq(view(1, 0), 0.76772));
    EXPECT_TRUE(epsilon_eq(view(1, 1), 0.60609));
    EXPECT_TRUE(epsilon_eq(view(1, 2), 0.12122));
    EXPECT_TRUE(epsilon_eq(view(1, 3), -2.82843));

    EXPECT_TRUE(epsilon_eq(view(2, 0), -0.35857));
    EXPECT_TRUE(epsilon_eq(view(2, 1), 0.59761));
    EXPECT_TRUE(epsilon_eq(view(2, 2), -0.71714));
    EXPECT_TRUE(epsilon_eq(view(2, 3), 0.00000));

    EXPECT_TRUE(epsilon_eq(view(3, 0), 0.0000));
    EXPECT_TRUE(epsilon_eq(view(3, 1), 0.0000));
    EXPECT_TRUE(epsilon_eq(view(3, 2), 0.0000));
    EXPECT_TRUE(epsilon_eq(view(3, 3), 1.0000));

    from = Point(0, 0, 8);
    to = Point(0, 0, 0);
    up = Vector(0, 1, 0);
    view = viewTransform(from, to, up);

    Matrix matrix = translationMatrix(0, 0, -8);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            EXPECT_TRUE(epsilon_eq(view(i, j), matrix(i, j)));
        }
    }
}

TEST(SceneTest, constructingCamera) {
    Camera camera(160, 120, M_PI / 2);
    EXPECT_FLOAT_EQ(camera.hsize(), 160.0);
    EXPECT_FLOAT_EQ(camera.vsize(), 120);
    
    Matrix transform = camera.transform();
    EXPECT_FLOAT_EQ(transform(0, 0), 1.0);
    EXPECT_FLOAT_EQ(transform(1, 1), 1.0);
    EXPECT_FLOAT_EQ(transform(2, 2), 1.0);
    EXPECT_FLOAT_EQ(transform(3, 3), 1.0);
}

TEST(SceneTest, cameraSize) {
    Camera camera(200, 125, M_PI/2);
    EXPECT_FLOAT_EQ(0.01, camera.pixelSize());

    Camera camera2(125, 200, M_PI / 2);
    EXPECT_FLOAT_EQ(0.01, camera2.pixelSize());
}

TEST(SceneTest, rayThroughCamera) {
    Camera camera(201, 101, M_PI/2);
    Ray ray = camera.calculateRayForPixel(100, 50);

    Tuple origin = ray.origin();
    Tuple direction = ray.direction();
    EXPECT_FLOAT_EQ(origin.x, 0.0);
    EXPECT_FLOAT_EQ(origin.y, 0.0);
    EXPECT_FLOAT_EQ(origin.z, 0.0);

    EXPECT_FLOAT_EQ(direction.x, 0.0);
    EXPECT_TRUE(epsilon_eq(direction.y, 0.0));
    EXPECT_FLOAT_EQ(direction.z, -1.0);

    Ray secondRay = camera.calculateRayForPixel(0, 0);

    origin = secondRay.origin();
    direction = secondRay.direction();
    EXPECT_FLOAT_EQ(origin.x, 0.0);
    EXPECT_FLOAT_EQ(origin.y, 0.0);
    EXPECT_FLOAT_EQ(origin.z, 0.0);

    EXPECT_TRUE(epsilon_eq(direction.x, 0.66519));
    EXPECT_TRUE(epsilon_eq(direction.y, 0.33259));
    EXPECT_TRUE(epsilon_eq(direction.z, -0.66851));

    Matrix transform = rotationY(M_PI/4) * translationMatrix(0, -2, 5);
    camera.setTransform(transform);
    Ray thirdRay = camera.calculateRayForPixel(100, 50);

    origin = thirdRay.origin();
    direction = thirdRay.direction();
    EXPECT_FLOAT_EQ(origin.x, 0.0);
    EXPECT_FLOAT_EQ(origin.y, 2.0);
    EXPECT_FLOAT_EQ(origin.z, -5.0);

    float value = sqrt(2) / 2;

    EXPECT_TRUE(epsilon_eq(direction.x, value));
    EXPECT_TRUE(epsilon_eq(direction.y, 0));
    EXPECT_TRUE(epsilon_eq(direction.z, -value));

}

TEST(SceneTest, renderWithCamera) {
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

    Tuple from = Point(0, 0, -5);
    Tuple to = Point(0, 0, 0);
    Tuple up = Vector(0, 1, 0);
    transform = viewTransform(from, to, up);
    Camera camera(11, 11, M_PI / 2, transform);

    Ray ray = camera.calculateRayForPixel(5, 5);
    Color defaultColor(0.0, 0.0, 0.0);
    Color result = defaultWorld.colorAt(ray, defaultColor);
    std::string info = result.debugString();
    printf("%s \n", info.c_str());

    EXPECT_FLOAT_EQ(result.r(), 0.38066);
    EXPECT_FLOAT_EQ(result.g(), 0.47583);
    EXPECT_FLOAT_EQ(result.b(), 0.2855);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}