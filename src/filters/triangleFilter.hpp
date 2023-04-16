#pragma once
#include "filter.h"

namespace pbrt {

class TriangleFilter : public Filter {
public:
    TriangleFilter(const vector2f &radius) : Filter(radius) {}
    float Evaluate(const Point2f &p) const {
        return std::max(0.f, radius.x - std::abs(p.x)) *
               std::max(0.f, radius.y - std::abs(p.y));
    }
};

};