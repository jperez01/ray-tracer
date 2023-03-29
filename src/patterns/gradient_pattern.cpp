#include "patterns/gradient_pattern.h"
#include <math.h>

GradientPattern::GradientPattern(Color &a, Color &b) :
    m_colora(a),
    m_colorb(b),
    m_transform(Transform()) {}

GradientPattern::GradientPattern(Color &a, Color &b, Transform transform) :
    m_colora(a),
    m_colorb(b),
    m_transform(transform) {}

Color GradientPattern::getColorAt(Point3f &point, Transform& transform) {
    Point3f object_point = transform(point);

    Transform inverse = m_transform.GetInverseMatrix();
    Point3f pattern_point = inverse(object_point);

    Color color_distance = m_colorb - m_colora;
    float fraction = pattern_point.x - floor(pattern_point.x);

    return m_colora + color_distance * fraction;
}

Color GradientPattern::getColorAt(Point3f &point) {
    Color color_distance = m_colorb - m_colora;
    float fraction = point.x - floor(point.x);

    return m_colora + color_distance * fraction;
}