#include "primitives/intersections.h"

#include <algorithm>
#include "primitives/math.h"

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

void Intersections::sortIntersections() {
    std::sort(m_intersections.begin(), m_intersections.end(),
    [](const Intersection &lhs, const Intersection &rhs) {
        return rhs.m_time > lhs.m_time;
    });
}

std::optional<Intersection> Intersections::hitOptional() {
    if (!m_intersections.size()) return std::nullopt;
    
    std::optional<Intersection> hit;
    for (Intersection &intersection : m_intersections) {
        if (intersection.m_time < 0) continue;
        if (epsilon_eq(intersection.m_time, 0.000)) continue;

        if (!hit.has_value() || intersection.m_time < hit.value().m_time) {
            hit = std::optional<Intersection>(intersection);
        }
    }
    return hit;
}

Intersection Intersections::hit() {
    if (!m_intersections.size()) return Intersection{};
    
    Intersection hit;
    for (Intersection &intersection : m_intersections) {
        if (intersection.m_time < 0) continue;

        if (hit.m_time < 0 || intersection.m_time < hit.m_time) {
            hit = intersection;
        }
    }
    return hit;
}

void Intersections::merge(Intersections &other) {
    std::vector<Intersection> merged;
    std::vector<Intersection>::const_iterator other_i = other.m_intersections.begin();
    std::vector<Intersection>::const_iterator i = m_intersections.begin();

    while (other_i != other.m_intersections.end() && i != m_intersections.end()) {
        Intersection other_int = *other_i;
        Intersection this_int = *i;
        if (other_int.m_time < this_int.m_time) {
            merged.push_back(other_int);
            other_i++;
        } else {
            merged.push_back(this_int);
            i++;
        }
    }

    while (other_i != other.m_intersections.end()) {
        Intersection other_int = *other_i;
        merged.push_back(other_int);
        other_i++;
    }

    while (i != m_intersections.end()) {
        Intersection this_int = *i;
        merged.push_back(this_int);
        i++;
    }

    m_intersections = merged;
}