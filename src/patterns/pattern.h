#pragma once

#include "primitives/color.h"
#include "core/transform.h"

using pbrt::Transform;
using pbrt::Point3f;

class Pattern {
    public:
        virtual ~Pattern() { }
        virtual Color getColorAt(Point3f &point) = 0;
        virtual Color getColorAt(Point3f &point, Transform &transform) = 0;
};