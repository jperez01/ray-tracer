#ifndef RTC_SHAPE
#define RTC_SHAPE

class Intersections;
class Intersection;

#include <optional>

#include "materials/material.h"

#include "primitives/ray.h"
#include "primitives/intersections.h"

#include "shapes/bounds.h"

#include "core/transform.h"
using pbrt::Transform;

class Shape {
    public:
        Shape();
        Shape(const Transform *objectToWorld, const Transform *worldToObject,
            bool reverseOrientation);
        virtual ~Shape() { }

        Bounds unitBounds();
        Vector3f globalNormal(Point3f &position, Intersection &i);
        bool includes(Shape *other);
        
        virtual Vector3f surfaceNormal(Point3f &position, Intersection &i) = 0;
        virtual void findIntersection(Ray &ray, Intersections &solutions) = 0;

        inline Shape* parent() { return m_parent; }
        inline void setParent(Shape* shape) { m_parent = shape; }

        const Transform *objectToWorld, *worldToObject;
        bool reverseOrientation;
        bool transformSwapsHandedness;
        Material material;

    private:
        Shape* m_parent = nullptr;
};

Point3f convertWorldToObject(Shape* &shape, Point3f &point);
Vector3f normalToWorld(Shape* &shape, Vector3f &normal);
Bounds childBounds(Shape *child);

#endif