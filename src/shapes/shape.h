#ifndef RTC_SHAPE
#define RTC_SHAPE

class Intersections;
#include <optional>
#include "primitives/tuple.h"
#include "primitives/matrix.h"
#include "shapes/material.h"
#include "primitives/ray.h"
#include "primitives/intersections.h"

class Shape {
    public:
        virtual Tuple surfaceNormal(Tuple &position) = 0;
        virtual void findIntersection(Ray &ray, Intersections &solutions) = 0;
        virtual ~Shape() { }
        virtual Material material() = 0;
        virtual std::optional<Matrix> transform() = 0;
};

#endif