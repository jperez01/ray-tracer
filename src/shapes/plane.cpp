#include "shapes/plane.h"

Plane::Plane() {
    m_transform = std::optional<Matrix>{};
    m_material = Material{};
    m_point = Point(0, 0, 0);
    m_normal = Vector(0, 1, 0);
}

Plane::Plane(Tuple &point, Tuple &normal) {
    m_point = point;
    m_normal = normal;
    m_transform = std::optional<Matrix>{};
    m_material = Material{};
}

Plane::Plane(Tuple &point, Tuple &normal, Material &material) {
    m_point = point;
    m_normal = normal;
    m_transform = std::optional<Matrix>{};
    m_material = Material{};
}

Plane::Plane(Tuple &point, Tuple &normal, Matrix &transform, Material &material) {
    m_point = point;
    m_normal = normal;
    m_transform = transform;
    m_material = material;
}

Tuple Plane::surfaceNormal(Tuple &position) {
    return m_normal;
}

void Plane::setTransform(Matrix &matrix) {
    m_transform = std::optional<Matrix>{matrix};
}

void Plane::setMaterial(Material &material) {
    m_material = material;
}

void Plane::findIntersection(Ray &givenRay, Intersections &results) {
    Ray ray;
    if (this->transform().has_value()) {
        Matrix transform = this->transform().value().inverse();
        ray = transformRay(givenRay, transform);
    } else ray = givenRay;

    float denom = dot(m_normal, givenRay.direction());

    if (abs(denom) > 0.00001) {
        Tuple pointDiff = m_point - givenRay.origin();
        float t = dot(pointDiff, m_normal) / denom;
        if (t >= 0) {
            Intersection i(t, this);
            results.add(i);
        }
    }
}