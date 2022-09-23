#include "primitives/ray.h"
#include "primitives/tuple.h"

Ray::Ray() {
    m_origin = Tuple(0, 0, 0);
    m_direction = Tuple(0, 0, 0);
}

Ray::Ray(Tuple origin, Tuple direction) {
    m_origin = origin;
    m_direction = direction;
}

Tuple Ray::position(float time) {
    return this->origin() + this->direction() * time;
}

Ray transformRay(Ray &ray, Matrix &matrix) {
    return Ray(matrix * ray.origin(), matrix * ray.direction());
}