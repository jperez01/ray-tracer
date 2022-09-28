#include "primitives/intersections.h"

#include <optional>

Intersections::Intersections() {
    m_intersections = std::vector<Intersection>{};
}

Intersections::Intersections(std::vector<Intersection> &intersections) {
    m_intersections = intersections;
}

int Intersections::size() {
    return m_intersections.size();
}

Intersection Intersections::operator[](int index) {
    return m_intersections[index];
}

void Intersections::add(Intersection &intersection) {
    m_intersections.push_back(intersection);
}

Intersection Intersections::hit() {
    if (!m_intersections.size()) return Intersection{};

    Intersection hit;
    for (Intersection intersection : m_intersections) {
        if (intersection.m_time < 0) continue;

        if (hit.m_time < 0 || intersection.m_time < hit.m_time) {
            hit = intersection;
        }
    }

    return hit;
}