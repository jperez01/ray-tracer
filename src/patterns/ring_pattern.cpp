#include "patterns/ring_pattern.h"
#include <math.h>

RingPattern::RingPattern(Color &a, Color &b) :
    m_colora(a),
    m_colorb(b),
    m_transform(std::optional<Matrix>{}) {}

RingPattern::RingPattern(Color &a, Color &b, Matrix transform) :
    m_colora(a),
    m_colorb(b),
    m_transform(std::optional<Matrix>{transform}) {}

Color RingPattern::getColorAt(Tuple &point, Shape &shape) {
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

    int value = (int) sqrt(pattern_point.x * pattern_point.x + pattern_point.z * pattern_point.z);
    if (value % 2 == 0) return m_colora;
    else return m_colorb;
}

Color RingPattern::getColorAt(Tuple &point) {
    int value = (int) sqrt(point.x * point.x + point.z * point.z);
    if (value % 2 == 0) return m_colora;
    else return m_colorb;
}