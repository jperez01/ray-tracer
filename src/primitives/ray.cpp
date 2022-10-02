#include "primitives/ray.h"
#include "primitives/tuple.h"

#include <sstream>

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

void Ray::setOrigin(Tuple origin) {
    m_origin = origin;
}

void Ray::setDirection(Tuple direction) {
    m_direction = direction;
}
    

std::string Ray::debugString() {
    std::stringstream stream;

    stream << "origin: ";
    stream << m_origin.x;
    stream << " ";
    stream << m_origin.y;
    stream << " ";
    stream << m_origin.z;
    stream << " ";
    stream << m_origin.w;
    stream << "\n";

    stream << "direction: ";
    stream << m_direction.x;
    stream << " ";
    stream << m_direction.y;
    stream << " ";
    stream << m_direction.z;
    stream << " ";
    stream << m_direction.w;
    stream << "\n";

    return stream.str();
}

Ray transformRay(Ray &ray, Matrix &matrix) {
    return Ray(matrix * ray.origin(), (matrix * ray.direction()));
}