#include "shapes/bounds.h"

#include <cmath>

using namespace rtutil;

Bounds::Bounds() {
    m_min = createPoint(-1, -1, -1);
    m_max = createPoint(1, 1, 1);
}

Bounds::Bounds(Point min, Point max) :
    m_min(min),
    m_max(max) {}

void Bounds::extendTo(Point &point) {
    m_min = createPoint(std::min(point.x, m_min.x),
    std::min(point.y, m_min.y),
    std::min(point.z, m_min.z));

    m_max = Point(std::max(point.x, m_min.x),
    std::max(point.y, m_min.y),
    std::max(point.z, m_min.z));
}

void Bounds::merge(Bounds &other) {
    if (m_min == createPoint(0, 0, 0) && m_max == createPoint(0, 0, 0)) {
        m_min = other.min();
        m_max = other.max();
    } else {
        m_min = createPoint(std::min(other.min().x, m_min.x),
        std::min(other.min().y, m_min.y),
        std::min(other.min().z, m_min.z));

        m_max = createPointoint(std::max(other.max().x, m_min.x),
        std::max(other.max().y, m_min.y),
        std::max(other.max().z, m_min.z));
    }
}

Point Bounds::center() {
    return (m_max + m_min) * 0.5;
}