#include "shapes/sphere.h"
#include "primitives/intersection.h"
#include "primitives/intersections.h"
#include "primitives/ray.h"
#include "primitives/tuple.h"

#include <math.h>
#include <iostream>

Sphere::Sphere(Tuple center, float radius) {
    m_center = center;
    m_radius = radius;
    m_color = Color(1.0, 0.0, 0.0);
    m_transform = std::optional<Matrix>{};
}

Sphere::Sphere(Tuple center, float radius, Color color) {
    m_center = center;
    m_radius = radius;
    m_color = color;
    m_transform = std::optional<Matrix>{};
}

Sphere::Sphere(Tuple center, float radius, Color color, Matrix &transform) {
    m_center = center;
    m_radius = radius;
    m_color = color;
    m_transform = std::optional<Matrix>{transform};
}

Intersections Sphere::findIntersection(Ray &givenRay) {
    Ray ray;
    if (m_transform.has_value()) {
        Matrix transform = m_transform.value().inverse();
        ray = transformRay(givenRay, transform);
    } else ray = givenRay;

    Tuple from_sphere_to_ray = ray.origin() - this->center();

    float a = dot(ray.direction(), ray.direction());
    float b = 2 * dot(ray.direction(), from_sphere_to_ray);
    float c = dot(from_sphere_to_ray, from_sphere_to_ray) - this->radius();

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) return Intersections(std::vector<Intersection>{});

    float two_a = 2 * a;
    float sqrt_dis = sqrt(discriminant);

    Intersection inter1 = Intersection((- b + sqrt_dis) / two_a, this);
    Intersection inter2 = Intersection((- b - sqrt_dis) / two_a, this);

    std::vector<Intersection> solutions;
    if (inter1.time() > inter2.time()) {
        solutions.push_back(inter2);
        solutions.push_back(inter1);
    } else {
        solutions.push_back(inter1);
        solutions.push_back(inter2);
    }

    return Intersections(solutions);
}

Tuple Sphere::surfaceNormal(Tuple position) {
    return (position - m_center).normalized();
}