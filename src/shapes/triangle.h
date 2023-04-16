#pragma once
#include "shapes/shape.h"

class Triangle : public Shape {
    public:
        Triangle(const Transform *objectToWorld, const Transform *worldToObject,
            bool reverseOrientation, Point3f v1 = Point3f(1, 0, 0), Point3f v2 = Point3f(0, 1, 0),
            Point3f v3 = Point3f(0, 0, 1));
        ~Triangle() = default;

        void calculateInfo();
        void findIntersection(Ray &givenRay, Intersections &solutions);
        Vector3f surfaceNormal(Point3f &point, Intersection &i);
        Bounds unitBounds();

        inline Point3f v1() { return m_vertex1; }
        inline Point3f v2() { return m_vertex2; }
        inline Point3f v3() { return m_vertex3; }
        inline Vector3f normal() { return m_normal; }
        inline Vector3f e1() { return m_e1; }
        inline Vector3f e2() { return m_e2; }

    private:
        Point3f m_vertex1, m_vertex2, m_vertex3;
        Vector3f m_e1, m_e2, m_normal;
};