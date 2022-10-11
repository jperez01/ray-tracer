#include "patterns/striped_pattern.h"

StripedPattern::StripedPattern(Color &a, Color &b) :
    m_colora(a),
    m_colorb(b),
    m_transform(std::optional<Matrix>{}) {}

StripedPattern::StripedPattern(Color &a, Color &b, Matrix transform) :
    m_colora(a),
    m_colorb(b),
    m_transform(std::optional<Matrix>{transform}) {}

Color StripedPattern::getColorAt(Tuple &point, Shape &shape) {
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

    int x = (int)pattern_point.x;
    if (x % 2 == 0) return m_colora;
    else return m_colorb;
}

Color StripedPattern::getColorAt(Tuple &point) {
    int x = (int)point.x;
    if (x % 2 == 0) return m_colora;
    else return m_colorb;
}