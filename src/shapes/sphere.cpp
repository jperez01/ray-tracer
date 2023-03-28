#include "shapes/sphere.h"

#include <math.h>
#include <iostream>

using namespace rtutil;

Sphere::Sphere() : Shape(nullptr, nullptr, false), m_radius(1.0f) {}

Sphere::Sphere(const glm::mat4 *objectToWorld, const glm::mat4 *worldToObject,
    bool reverseOrientation, float radius) :
    Shape(objectToWorld, worldToObject, reverseOrientation),
    m_radius(radius) {}

Shape* GlassySphere() {
    auto sphere = new Sphere();
    auto glass = Material{};
    glass.setTransparency(1.0);
    glass.setRefractiveIndex(GLASS);
    sphere->material = glass;
    return sphere;
}

void Sphere::findIntersection(Ray &givenRay, Intersections &solutions) {
    Ray ray;
    glm::mat4 transform = *objectToWorld;
    ray = transformRay(givenRay, transform);

    float a = glm::dot(ray.direction(), ray.direction());
    float b = 2 * glm::dot(ray.direction(), ray.origin());
    float c = glm::dot(ray.origin(), ray.origin()) - m_radius;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return;

    float two_a = 2 * a;
    float sqrt_dis = sqrt(discriminant);

    Intersection inter1{(-b + sqrt_dis) / two_a, this};
    Intersection inter2{(-b - sqrt_dis) / two_a, this};

    if (inter1.m_time > inter2.m_time) {
        solutions.add(inter2);
        solutions.add(inter1);
    } else {
        solutions.add(inter1);
        solutions.add(inter2);
    }
}

Vector Sphere::surfaceNormal(Point &position, Intersection &i) {
    glm::mat4 inverse = (*worldToObject);
    glm::mat4 transpose = glm::transpose(inverse);

    Point object_point = inverse * position;
    Vector object_normal = object_point;
    Vector world_normal = transpose * object_normal;
    world_normal.w = 0;
    return glm::normalize(world_normal);
}

