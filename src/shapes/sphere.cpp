#include "shapes/sphere.h"
#include "primitives/intersections.h"
#include "primitives/ray.h"
#include "primitives/tuple.h"

#include <math.h>
#include <iostream>

Sphere::Sphere() {
    m_center = Point(0.0, 0.0, 0.0);
    m_radius = 1.0;
    m_material = Material();
    m_transform = std::optional<Matrix>{};
}

Sphere::Sphere(Tuple &center, float radius) {
    m_center = center;
    m_radius = radius;
    m_material = Material();
    m_transform = std::optional<Matrix>{};
}

Sphere::Sphere(const Material &material) {
    m_center = Point(0.0, 0.0, 0.0);
    m_radius = 1.0;
    m_material = material;
    m_transform = std::optional<Matrix>{};
}

Sphere::Sphere(const Material &material, Matrix &transform) {
    m_center = Point(0.0, 0.0, 0.0);
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
    m_center = center;
    m_radius = radius;
    m_material = material;
    m_transform = std::optional<Matrix>(transform);
}

Shape* GlassySphere() {
    auto sphere = new Sphere();
    auto glass = Material{};
    glass.setTransparency(1.0);
    glass.setRefractiveIndex(GLASS);
    sphere->setMaterial(glass);
    return sphere;
}

void Sphere::setTransform(Matrix &matrix) {
    m_transform = std::optional<Matrix>{matrix};
}

void Sphere::setMaterial(Material &material) {
    m_material = material;
}

void Sphere::findIntersection(Ray &givenRay, Intersections &solutions) {
    Ray ray;
    if (this->transform().has_value()) {
        Matrix transform = this->transform().value().inverse();
        ray = transformRay(givenRay, transform);
    } else ray = givenRay;

    Tuple from_sphere_to_ray = ray.origin() - this->center();

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

Tuple Sphere::surfaceNormal(Tuple &position, Intersection &i) {
    if (m_transform.has_value()) {
        Matrix inverse = m_transform.value().inverse();
        Matrix transpose = inverse.transpose();

        Tuple object_point = inverse * position;
        Tuple object_normal = object_point - m_center;
        Tuple world_normal = transpose * object_normal;
        world_normal.w = 0;
        return world_normal.normalized();
    } else return (position - m_center).normalized();
}

