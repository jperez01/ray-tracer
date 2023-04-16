#include "shapes/triangle.h"
#include <cmath>

Triangle::Triangle(const Transform *objectToWorld, const Transform *worldToObject,
    bool reverseOrientation, Point3f v1, Point3f v2, Point3f v3) :
    Shape(objectToWorld, worldToObject, reverseOrientation),
    m_vertex1(v1), m_vertex2(v2), m_vertex3(v3) {
        calculateInfo();
    }

void Triangle::calculateInfo() {
    m_e1 = m_vertex2 - m_vertex1;
    m_e2 = m_vertex3 - m_vertex1;
    m_normal = Normalize(Cross(m_e2, m_e1));
}

Vector3f Triangle::surfaceNormal(Point3f &point, Intersection &i) {
    return m_normal;
}

void Triangle::findIntersection(Ray &givenRay, Intersections &solutions) {
    Vector3f cross_dir = Cross(givenRay.direction, m_e2);

    float determinant = Dot(cross_dir, m_e1);
    if (fabs(determinant) < 0.0001) return;

    float f = 1.0 / determinant;
    Vector3f v1_to_origin = givenRay.origin - m_vertex1;
    float u = f * Dot(v1_to_origin, cross_dir);
    if (u < 0.0 || u > 1.0) return;

    Vector3f origin_cross_e1 = Cross(v1_to_origin, m_e1);
    float v = f * Dot(givenRay.direction, origin_cross_e1);
    if (v < 0.0 || (u + v) > 1.0) return;

    float t = f * Dot(m_e2, origin_cross_e1);
    Intersection result{t, this};
    solutions.add(result);
}