#pragma once

#include "patterns/pattern.h"
#include "shapes/shape.h"

class RingPattern : public Pattern {
    public:
        RingPattern(Color &a, Color &b);
        RingPattern(Color &a, Color &b, Transform transform);

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