#ifndef RTC_PATTERN
#define RTC_PATTERN

class Material;
class Shape;
#include "primitives/color.h"
#include "shapes/shape.h"

class Pattern {
    public:
        virtual ~Pattern() { }
        virtual Color getColorAt(Tuple &point, Shape &shape) = 0;
};

#endif