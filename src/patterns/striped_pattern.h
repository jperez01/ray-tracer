#ifndef RTC_STRIPED_PATTERN
#define RTC_STRIPED_PATTERN

#include "patterns/pattern.h"
#include "shapes/shape.h"

class StripedPattern : public Pattern {
    public:
        StripedPattern(Color &a, Color &b);
        StripedPattern(Color &a, Color &b, Transform transform);

        Color getColorAt(Point3f &point, Transform& transform);
        Color getColorAt(Point3f &point);

        inline Color colorA() { return m_colora; }
        inline Color colorB() { return m_colorb; }
        inline Transform transform() { return m_transform; }

    private:
        Color m_colora;
        Color m_colorb;
        Transform m_transform;
};

#endif