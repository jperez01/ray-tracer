#include "patterns/ring_pattern.h"
#include <math.h>

RingPattern::RingPattern(Color &a, Color &b) :
    m_colora(a),
    m_colorb(b),
    m_transform(Transform()) {}

RingPattern::RingPattern(Color &a, Color &b, Transform transform) :
    m_colora(a),
    m_colorb(b),
    m_transform(transform) {}

Color RingPattern::getColorAt(Point3f &point, Transform& transform) {
    Point3f object_point = transform(point);

    Transform inverse = m_transform.GetInverseMatrix();
    Point3f pattern_point = inverse(object_point);

    int value = (int) sqrt(pattern_point.x * pattern_point.x + 
        pattern_point.z * pattern_point.z);
    if (value % 2 == 0) return m_colora;
    else return m_colorb;
}

Color RingPattern::getColorAt(Point3f &point) {
    int value = (int) sqrt(point.x * point.x + point.z * point.z);
    if (value % 2 == 0) return m_colora;
    else return m_colorb;
}