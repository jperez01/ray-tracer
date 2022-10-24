#include "shapes/smooth_triangle.h"
#include <cmath>

SmoothTriangle::SmoothTriangle() :
    m_vertex1(Point(1, 0, 0)),
    m_vertex2(Point(0, 1, 0)),
    m_vertex3(Point(0, 0, 1)),
    m_normal1(Vector(0, 1, 0)),
    m_normal2(Vector(0, 1, 0)),
    m_normal3(Vector(0, 1, 0)) {
        calculateInfo();
    }

SmoothTriangle::SmoothTriangle(Tuple &v1, Tuple &v2, Tuple &v3, Tuple &n1, Tuple &n2, Tuple &n3) :
    m_vertex1(v1),
    m_vertex2(v2),
    m_vertex3(v3),
    m_normal1(n1),
    m_normal2(n2),
    m_normal3(n3) {
        calculateInfo();
    }

void SmoothTriangle::setTransform(Matrix &transform) {
    m_transform = std::optional<Matrix>{transform};
}
void SmoothTriangle::setMaterial(Material &material) {
    m_material = material;
}

void SmoothTriangle::calculateInfo() {
    m_e1 = m_vertex2 - m_vertex1;
    m_e2 = m_vertex3 - m_vertex1;
}

Tuple SmoothTriangle::surfaceNormal(Tuple &point, Intersection &i) {
    return m_normal2 * i.m_u + m_normal3 * i.m_v + m_normal1 * (1.0 - i.m_u - i.m_v);
}

void SmoothTriangle::findIntersection(Ray &givenRay, Intersections &solutions) {
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
    Intersection result{t, this, u, v};
    solutions.add(result);
}

Bounds SmoothTriangle::unitBounds() {
    float minx = std::min(m_vertex1.x, std::min(m_vertex2.x, m_vertex3.x));
    float miny = std::min(m_vertex1.y, std::min(m_vertex2.y, m_vertex3.y));
    float minz = std::min(m_vertex1.z, std::min(m_vertex2.z, m_vertex3.z));

    float maxx = std::max(m_vertex1.x, std::max(m_vertex2.x, m_vertex3.x));
    float maxy = std::max(m_vertex1.y, std::max(m_vertex2.y, m_vertex3.y));
    float maxz = std::max(m_vertex1.z, std::max(m_vertex2.z, m_vertex3.z));

    return Bounds(Point(minx, miny, minz), Point(maxx, maxy, maxz));
}