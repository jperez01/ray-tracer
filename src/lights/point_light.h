#ifndef RTC_LIGHT_POINT
#define RTC_LIGHT_POINT

#include "primitives/tuple.h"
#include "primitives/color.h"
#include "shapes/shape.h"

class PointLight {
    public:
        PointLight(Color color, Tuple position);

        inline Color color() { return m_color; }
        inline Tuple position() { return m_position; }

    private:
        Tuple m_position;
        Color m_color;
};

Color calculateColorFromPoint(PointLight light, Tuple normal, Tuple position, Shape *shape);

#endif