#ifndef RTC_SHAPE
#define RTC_SHAPE

class Intersections;
class Intersection;
#include <optional>
#include "primitives/tuple.h"
#include "primitives/matrix.h"
#include "shapes/material.h"
#include "primitives/ray.h"
#include "primitives/intersections.h"
#include "shapes/bounds.h"

class Shape {
    public:
        virtual ~Shape() { }

        Bounds unitBounds();
        Tuple globalNormal(Tuple &position, Intersection &i);
        bool includes(Shape *other);
        
        virtual Tuple surfaceNormal(Tuple &position, Intersection &i) = 0;
        virtual void findIntersection(Ray &ray, Intersections &solutions) = 0;

        virtual Material material() = 0;
        virtual void setMaterial(Material &material) = 0;
        virtual std::optional<Matrix> transform() = 0;
        virtual void setTransform(Matrix &transform) = 0;
        inline Shape* parent() { return m_parent; }
        inline void setParent(Shape* shape) { m_parent = shape; }

    private:
        Shape* m_parent = nullptr;
};

Tuple worldToObject(Shape* &shape, Tuple &point);
Tuple normalToWorld(Shape* &shape, Tuple &normal);
Bounds childBounds(Shape *child);

#endif