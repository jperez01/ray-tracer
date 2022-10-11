#include "patterns/gradient_pattern.h"
#include <math.h>

GradientPattern::GradientPattern(Color &a, Color &b) :
    m_colora(a),
    m_colorb(b),
    m_transform(std::optional<Matrix>{}) {}

GradientPattern::GradientPattern(Color &a, Color &b, Matrix transform) :
    m_colora(a),
    m_colorb(b),
    m_transform(std::optional<Matrix>{transform}) {}

Color GradientPattern::getColorAt(Tuple &point, Shape &shape) {
    Tuple object_point;
    if (shape.transform().has_value()) {
        Matrix inverse = shape.transform().value().inverse();
        object_point = inverse * point;
    } else object_point = point;

    Tuple pattern_point;
    if (m_transform.has_value()) {
        Matrix inverse = m_transform.value().inverse();
        pattern_point = inverse * object_point;
    } else pattern_point = object_point;

    Color color_distance = m_colorb - m_colora;
    float fraction = pattern_point.x - floor(pattern_point.x);

    return m_colora + color_distance * fraction;
}

Color GradientPattern::getColorAt(Tuple &point) {
    Color color_distance = m_colorb - m_colora;
    float fraction = point.x - floor(point.x);

    return m_colora + color_distance * fraction;
}