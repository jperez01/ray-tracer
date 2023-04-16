#include "patterns/striped_pattern.h"

StripedPattern::StripedPattern(Color &a, Color &b) :
    m_colora(a),
    m_colorb(b),
    m_transform(Transform()) {}

StripedPattern::StripedPattern(Color &a, Color &b, Transform transform) :
    m_colora(a),
    m_colorb(b),
    m_transform(transform) {}

Color StripedPattern::getColorAt(Point3f &point, Transform& transform) {
    Point3f object_point = transform(point);

    Transform inverse = m_transform.GetInverseMatrix();
    Point3f pattern_point = inverse(object_point);

    int x = (int)pattern_point.x;
    if (x % 2 == 0) return m_colora;
    else return m_colorb;
}

Color StripedPattern::getColorAt(Point3f &point) {
    int x = (int)point.x;
    if (x % 2 == 0) return m_colora;
    else return m_colorb;
}