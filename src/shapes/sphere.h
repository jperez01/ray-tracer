#ifndef RTC_SPHERE
#define RTC_SPHERE

#include "shapes/material.h"
#include "shapes/shape.h"

#include "primitives/ray.h"
#include "primitives/intersections.h"

#include <vector>
#include <optional>

class Sphere : public Shape {
    public:
        Sphere(const glm::mat4 *objectToWorld, const glm::mat4 *worldToObject,
            bool reverseOrientation, float radius);
        Sphere();

        Vector globalNormal(Point &position, Intersection &i);
        void findIntersection(Ray &givenRay, Intersections &solutions);
        Vector surfaceNormal(Point &position, Intersection &i);

    private:
        float m_radius;
};

Shape* GlassySphere();
#endif