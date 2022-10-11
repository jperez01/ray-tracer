#pragma once

#include "patterns/pattern.h"
#include "shapes/shape.h"

class GradientPattern : public Pattern {
    public:
        GradientPattern(Color &a, Color &b);
        GradientPattern(Color &a, Color &b, Matrix transform);

        Color getColorAt(Tuple &point, Shape &shape);
        Color getColorAt(Tuple &point);

        inline Color colorA() { return m_colora; }
        inline Color colorB() { return m_colorb; }
        inline std::optional<Matrix> transform() { return m_transform; }

    private:
        Color m_colora;
        Color m_colorb;
        std::optional<Matrix> m_transform;
};