#ifndef RTC_SPHERE
#define RTC_SPHERE

#include "shapes/shape.h"

#include <vector>
#include <optional>

class Sphere : public Shape {
    public:
        Sphere(const Transform *objectToWorld, const Transform *worldToObject,
            bool reverseOrientation, float radius);
        Sphere();

        Vector3f globalNormal(Point3f &position, Intersection &i);
        void findIntersection(Ray &givenRay, Intersections &solutions);
        Vector3f surfaceNormal(Point3f &position, Intersection &i);

    private:
        float m_radius;
};

Shape* GlassySphere();
#endif