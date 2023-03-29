#include "shapes/sphere.h"

#include <math.h>
#include <iostream>

Sphere::Sphere() : Shape(nullptr, nullptr, false), m_radius(1.0f) {}

Sphere::Sphere(const Transform *objectToWorld, const Transform *worldToObject,
            bool reverseOrientation, float radius) :
    Shape(objectToWorld, worldToObject, reverseOrientation),
    m_radius(radius) {}

Shape* GlassySphere() {
    auto sphere = new Sphere();
    auto glass = Material{};
    glass.transparency = 1.0f;
    glass.refractive_index = GLASS;
    sphere->material = glass;
    return sphere;
}

void Sphere::findIntersection(Ray &givenRay, Intersections &solutions) {
    Transform inverse = *worldToObject;
    Ray ray = transformRay(givenRay, inverse);

    Vector3f from_sphere_to_ray = Vector3f(ray.origin);

    float a = Dot(ray.direction, ray.direction);
    float b = 2 * Dot(ray.direction, from_sphere_to_ray);
    float c = Dot(from_sphere_to_ray, from_sphere_to_ray) - m_radius;

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

Vector3f Sphere::surfaceNormal(Point3f &position, Intersection &i) {
    Point3f object_position = (*worldToObject)(position);
    Transform transpose = Transpose(*worldToObject);

    Vector3f object_normal = (*worldToObject)((Vector3f)object_position);
    return Normalize(transpose(object_normal));
}

