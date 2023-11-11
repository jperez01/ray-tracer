#pragma once
#include "core/filter.h"

namespace pbrt {

class BoxFilter : public Filter {
public:
    BoxFilter(const Vector2f &radius) : Filter(radius) {}
    float Evaluate(const Point2f &p) const {
        return 1.f;
    }
};

};