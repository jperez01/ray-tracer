#pragma once
#include "filter.h"

namespace pbrt {

class BoxFilter : public Filter {
public:
    BoxFilter(const vector2f &radius) : Filter(radius) {}
    float Evaluate(const Point2f &p) const {
        return 1.f;
    }
};

};