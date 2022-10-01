#include "shapes/sphere.h"
#include "primitives/intersections.h"
#include "primitives/ray.h"
#include "primitives/tuple.h"

#include <math.h>
#include <iostream>

Sphere::Sphere(Tuple &center, float radius) {
    m_center = center;
    m_radius = radius;
    m_material = Material();
    m_transform = std::optional<Matrix>{};
}

Sphere::Sphere(const Material &material, Matrix &transform) {
    m_center = Tuple(0.0, 0.0, 0.0);
    m_radius = 1.0;
    m_material = material;
    m_transform = std::optional<Matrix>(transform);
}

Sphere::Sphere(Tuple &center, float radius, const Material &material) {
    m_center = center;
    m_radius = radius;
    m_material = material;
    m_transform = std::optional<Matrix>{};
}

Sphere::Sphere(Tuple &center, float radius, const Material &material, Matrix &transform) {
    m_center =  center;
    m_radius = radius;
    m_material = material;
    m_transform = std::optional<Matrix>(transform);
}
void Sphere::findIntersection(Ray &givenRay, Intersections &solutions) {
    Ray ray;
    if (this->transform().has_value()) {
        Matrix transform = this->transform().value().inverse();
        ray = transformRay(givenRay, transform);
    } else ray = givenRay;

    Tuple from_sphere_to_ray = ray.origin() - this->center();
    from_sphere_to_ray = from_sphere_to_ray.normalized();

    float a = dot(ray.direction(), ray.direction());
    float b = 2 * dot(ray.direction(), from_sphere_to_ray);
    float c = dot(from_sphere_to_ray, from_sphere_to_ray) - this->radius();

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

void findIntersection(Sphere &sphere, Ray &givenRay, Intersections &solutions) {
    Ray ray;
    if (sphere.transform().has_value()) {
        Matrix transform = sphere.transform().value().inverse();
        ray = transformRay(givenRay, transform);
    } else ray = givenRay;

    Tuple from_sphere_to_ray = ray.origin() - sphere.center();

    float a = dot(ray.direction(), ray.direction());
    float b = 2 * dot(ray.direction(), from_sphere_to_ray);
    float c = dot(from_sphere_to_ray, from_sphere_to_ray) - sphere.radius();

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) return;

    float two_a = 2 * a;
    float sqrt_dis = sqrt(discriminant);

    Intersection inter1{(-b + sqrt_dis) / two_a};
    Intersection inter2{(-b - sqrt_dis) / two_a};

    if (inter1.m_time > inter2.m_time) {
        solutions.add(inter2);
        solutions.add(inter1);
    } else {
        solutions.add(inter1);
        solutions.add(inter2);
    }
}

Tuple Sphere::surfaceNormal(Tuple &position) {
    Tuple normal = position - m_center;
    if (m_transform.has_value()) {
        return (m_transform.value().inverse().transpose() * normal).normalized();
    } else return normal.normalized();
}