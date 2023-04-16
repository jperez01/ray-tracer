#ifndef RTC_LIGHT_DIRECTION
#define RTC_LIGHT_DIRECTION

#include "primitives/color.h"
#include "shapes/shape.h"

class DirectionalLight {
    public:
        DirectionalLight(Vector3f direction, Color color);
        Color calculateColorFromDirection(Vector3f &normal, const Vector3f &eye, Shape *shape);

    private:
        Vector3f m_direction;
        Color m_color;
};

#endif