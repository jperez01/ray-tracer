#include "primitives/intersection.h"
#include "primitives/intersections.h"

#include <optional>

Intersections::Intersections(std::vector<Intersection> intersections) {
    m_intersections = intersections;
}

int Intersections::size() {
    return m_intersections.size();
}

Intersection Intersections::operator[](int index) {
    return m_intersections[index];
}

std::optional<Intersection> Intersections::hit() {
    if (!m_intersections.size()) return std::nullopt;

    std::optional<Intersection> hit = std::nullopt;
    for (Intersection intersection : m_intersections) {
        if (intersection.time() < 0) continue;

        if (hit == std::nullopt || intersection.time() < hit.value().time()) {
            hit = std::optional<Intersection>(intersection);
        }
    }

    return hit;
}