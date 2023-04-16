#pragma once

#include "patterns/pattern.h"

class GradientPattern : public Pattern {
    public:
        GradientPattern(Color &a, Color &b);
        GradientPattern(Color &a, Color &b, Transform transform);

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