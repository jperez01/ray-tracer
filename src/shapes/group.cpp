#include "shapes/group.h"
#include <cmath>
#include <algorithm>

Group::Group() :
    m_children(std::vector<Shape*>{}),
    m_transform(std::optional<Matrix>{}),
    m_material(Material{}) {}

Group::Group(Matrix transform) :
    m_children(std::vector<Shape*>{}),
    m_transform(std::optional<Matrix>{transform}),
    m_material(Material{}) {}

void Group::setTransform(Matrix &matrix) {
    m_transform = std::optional<Matrix>{matrix};
}

void Group::setMaterial(Material &material) {
    m_material = material;
}

void Group::extendBounds(Shape* shape) {
    Bounds child_bounds = childBounds(shape);
    m_bounds.merge(child_bounds);
}

void Group::addShape(Shape* &shape) {
    extendBounds(shape);
    shape->setParent(this);
    shape->setMaterial(m_material);
    m_children.push_back(shape);
}

void Group::findIntersection(Ray &givenRay, Intersections &solutions) {
    float xmin, xmax, ymin, ymax, zmin, zmax;

    checkAxis(givenRay.origin().x, givenRay.direction().x, &xmin, &xmax,
        m_bounds.min().x, m_bounds.max().x);
    checkAxis(givenRay.origin().y, givenRay.direction().y, &ymin, &ymax,
        m_bounds.min().y, m_bounds.max().y);
    checkAxis(givenRay.origin().z, givenRay.direction().z, &zmin, &zmax,
        m_bounds.min().z, m_bounds.max().z);

    float tmin = std::fmax(xmin, std::fmax(ymin, zmin));
    float tmax = std::fmax(xmax, std::fmax(ymax, zmax));

    if (tmin > tmax) return;

    for (Shape* &object : m_children) {
        object->findIntersection(givenRay, solutions);
    }
}

void Group::checkAxis(float origin, float direction,
    float *tmin, float *tmax, float direction_min, float direction_max) {
    float tmin_numerator = direction_min - origin;
    float tmax_numerator = direction_max - origin;

    if (fabs(direction) >= 0.00001) {
        *tmin = tmin_numerator / direction;
        *tmax = tmax_numerator / direction;
    } else {
        *tmin = tmin_numerator * INFINITY;
        *tmax = tmax_numerator * INFINITY;
    }

    if (*tmin > *tmax) {
        std::swap(*tmax, *tmin);
    }
}