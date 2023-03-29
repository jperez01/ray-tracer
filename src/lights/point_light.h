#ifndef RTC_LIGHT_POINT
#define RTC_LIGHT_POINT

#include "primitives/color.h"
#include "shapes/shape.h"

class PointLight {
    public:
        PointLight(Color color, Point3f position);
        Color calculateColorFromPoint(Vector3f &normal, Point3f &position, const Vector3f &eye, Shape &shape, bool inShadow);

        inline Point3f position() { return m_position; }
    private:
        Point3f m_position;
        Color m_color;
};

#endif