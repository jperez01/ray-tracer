#include "shapes/triangle.h"
#include <cmath>

Triangle::Triangle() :
    m_vertex1(Point(1, 0, 0)),
    m_vertex2(Point(0, 1, 0)),
    m_vertex3(Point(0, 0, 1)) {
        calculateInfo();
    }

Triangle::Triangle(Tuple &v1, Tuple &v2, Tuple &v3) :
    m_vertex1(v1),
    m_vertex2(v2),
    m_vertex3(v3) {
        calculateInfo();
    }

void Triangle::setTransform(Matrix &transform) {
    m_transform = std::optional<Matrix>{transform};
}
void Triangle::setMaterial(Material &material) {
    m_material = material;
}

void Triangle::calculateInfo() {
    m_e1 = m_vertex2 - m_vertex1;
    m_e2 = m_vertex3 - m_vertex1;
    m_normal = cross(m_e2, m_e1).normalized();
}

Tuple Triangle::surfaceNormal(Tuple &point, Intersection &i) {
    return m_normal;
}

void Triangle::findIntersection(Ray &givenRay, Intersections &solutions) {
    Tuple cross_dir = cross(givenRay.direction(), m_e2);

    float determinant = dot(cross_dir, m_e1);
    if (fabs(determinant) < 0.0001) return;

    float f = 1.0 / determinant;
    Tuple v1_to_origin = givenRay.origin() - m_vertex1;
    float u = f * dot(v1_to_origin, cross_dir);
    if (u < 0.0 || u > 1.0) return;

    Tuple origin_cross_e1 = cross(v1_to_origin, m_e1);
    float v = f * dot(givenRay.direction(), origin_cross_e1);
    if (v < 0.0 || (u + v) > 1.0) return;

    float t = f * dot(m_e2, origin_cross_e1);
    Intersection result{t, this};
    solutions.add(result);
}