#include "primitives/ray.h"
#include "primitives/tuple.h"

#include <sstream>

Ray::Ray() {
    m_origin = rtutil::Point(0, 0, 0);
    m_direction = rtutil::Vector(0, 0, 0);
}

Ray::Ray(glm::vec4 origin, glm::vec4 direction) {
    m_origin = origin;
    m_direction = direction;
}

glm::vec4 Ray::position(float time) {
    return m_origin + m_direction * time;
}

void Ray::setOrigin(glm::vec4 origin) {
    m_origin = origin;
}

void Ray::setDirection(glm::vec4 direction) {
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

Ray transformRay(Ray &ray, glm::mat4 &matrix) {
    return Ray(matrix * ray.origin(), (matrix * ray.direction()));
}