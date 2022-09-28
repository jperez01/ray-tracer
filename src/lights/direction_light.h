#ifndef RTC_LIGHT_DIRECTION
#define RTC_LIGHT_DIRECTION

#include "primitives/tuple.h"
#include "primitives/color.h"
#include "shapes/shape.h"

class DirectionalLight {
    public:
        DirectionalLight(Tuple direction, Color color);

        inline Tuple direction() { return m_direction; }
        inline Color color() { return m_color; }

    private:
        Tuple m_direction;
        Color m_color;
};

Color calculateColorFromDirection(DirectionalLight &light, Tuple &normal, const Tuple &eye, Shape *shape);

#endif