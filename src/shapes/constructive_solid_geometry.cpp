#include "shapes/constructive_solid_geometry.h"

ConstructiveSolidGeometry::ConstructiveSolidGeometry(Shape* left, Shape* right,
    IntersectionStrategy *strategy) {
    m_left = left;
    left->setParent(this);
    m_right = right;
    right->setParent(this);
    m_strategy = strategy;
}

Tuple ConstructiveSolidGeometry::surfaceNormal(Tuple &position, Intersection &i) {
    return Vector(0, 0, position.z);
}

void ConstructiveSolidGeometry::findIntersection(Ray &ray, Intersections &solutions) {
    Intersections temp;
    m_left->findIntersection(ray, temp);
    m_right->findIntersection(ray, temp);

    Intersections filtered = filterIntersections(temp);
    solutions.merge(filtered);
}

Intersections ConstructiveSolidGeometry::filterIntersections(Intersections &solutions) {
    std::vector<Intersection> filtered;
    bool in_left = false;
    bool in_right = false;

    for (auto &hit : solutions.intersectionsList()) {
        Shape* shape = hit.m_shape;
        bool left_hit = m_left->includes(shape);

        if (m_strategy->intersectionAllowed(left_hit, in_left, in_right)) filtered.push_back(hit);

        if (left_hit) in_left = !in_left;
        else in_right = !in_right;
    }

    return Intersections(filtered);
}

Bounds ConstructiveSolidGeometry::unitBounds() {
    Bounds bounds = childBounds(m_left);
    Bounds right_bounds = childBounds(m_right);
    bounds.merge(right_bounds);

    return bounds;
}

bool ConstructiveSolidGeometry::includes(Shape *other) {
    return m_left->includes(other) || m_right->includes(other);
}