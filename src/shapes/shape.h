#ifndef RTC_SHAPE
#define RTC_SHAPE

#include <optional>
#include "primitives/tuple.h"
#include "primitives/matrix.h"
#include "shapes/material.h"

class Shape {
    public:
        virtual Tuple surfaceNormal(Tuple &position) = 0;
        virtual ~Shape() { }
        virtual Material material() = 0;


};

#endif