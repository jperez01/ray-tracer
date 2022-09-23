#ifndef RTC_SHAPE
#define RTC_SHAPE

#include "primitives/tuple.h"
#include "primitives/color.h"

class Shape {
    public:
        virtual Tuple surfaceNormal(Tuple position) = 0;
        virtual ~Shape() { }
        virtual Color color() = 0;
};

#endif