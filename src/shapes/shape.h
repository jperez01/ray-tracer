#ifndef RTC_SHAPE
#define RTC_SHAPE

class Intersections;
class Intersection;
#include <optional>

#include "shapes/material.h"
#include "shapes/bounds.h"

#include "primitives/ray.h"
#include "primitives/intersections.h"

class Shape {
    public:
        Shape(const glm::mat4 *objectToWorld, const glm::mat4 *worldToObject,
            bool reverseOrientation);
        virtual ~Shape();

        Bounds unitBounds();
        Vector globalNormal(Point &position, Intersection &i);
        bool includes(Shape *other);
        
        virtual Vector surfaceNormal(Point &position, Intersection &i) = 0;
        virtual void findIntersection(Ray &ray, Intersections &solutions) = 0;

        inline Shape* parent() { return m_parent; }
        inline void setParent(Shape* shape) { m_parent = shape; }

        Material material;
        const glm::mat4 *objectToWorld, *worldToObject;
        const bool reverseOrientation;
        const bool transformSwapsHandedness;

    private:
        Shape* m_parent = nullptr;
};

Point convertWorldToObject(Shape* &shape, Point &point);
Vector normalToWorld(Shape* &shape, Vector &normal);
Bounds childBounds(Shape *child);

#endif