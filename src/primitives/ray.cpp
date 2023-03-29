#include "primitives/ray.h"

#include <sstream>

Ray::Ray() {
    origin = Point3f(0, 0, 0);
    direction = Vector3f(0, 0, 0);
}

Ray::Ray(Point3f origin, Vector3f direction) {
    this->origin = origin;
    this->direction = direction;
}

Point3f Ray::position(float time) {
    return origin + direction * time;
}

std::string Ray::debugString() {
    std::stringstream stream;

    stream << "origin: ";
    stream << origin.x;
    stream << " ";
    stream << origin.y;
    stream << " ";
    stream << origin.z;
    stream << " ";
    stream << 1.0;
    stream << "\n";

    stream << "direction: ";
    stream << direction.x;
    stream << " ";
    stream << direction.y;
    stream << " ";
    stream << direction.z;
    stream << " ";
    stream << 0.0;
    stream << "\n";

    return stream.str();
}

Ray transformRay(Ray &ray, Transform &matrix) {
    return Ray(matrix(ray.origin), matrix(ray.direction));
}