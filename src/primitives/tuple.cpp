#include "primitives/math.h"
#include "tuple.h"
#include <cmath>
#include <sstream>

Tuple::Tuple(float v1, float v2, float v3) :
            x(v1), y(v2), z(v3), w(0) {}

Tuple::Tuple(float v1, float v2, float v3, float v4) : 
            x(v1), y(v2), z(v3), w(v4) {}

Tuple::Tuple() : x(0), y(0), z(0), w(0) {}

Tuple Point(float x, float y, float z) {
    return Tuple(x, y, z, 1.0);
}

Tuple Vector(float x, float y, float z) {
    return Tuple(x, y, z, 0.0);
}

bool Tuple::isPoint() {
    return epsilon_eq(1.0, w);
}

bool Tuple::isVector() {
    return epsilon_eq(0.0, w);
}

float Tuple::magnitude() {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

Tuple Tuple::operator+(const Tuple second) {
    return Tuple(x + second.x, y + second.y, z + second.z, w + second.w);
}

Tuple Tuple::operator-(const Tuple second) {
    return Tuple(x - second.x, y - second.y, z - second.z, w - second.w);
}

Tuple Tuple::operator-() {
    return Tuple(-x, -y, -z, -w);
}

Tuple Tuple::operator*(float mult) {
    return Tuple(x * mult, y * mult, z * mult, w * mult);
}

Tuple Tuple::operator/(float mult) {
    return Tuple(x / mult, y / mult, z / mult, w / mult);
}

bool Tuple::operator==(Tuple other) {
    return epsilon_eq(x, other.x) &&
        epsilon_eq(y, other.y) &&
        epsilon_eq(z, other.z) &&
        epsilon_eq(w, other.w);
}

Tuple Tuple::normalized() {
    float magnitude = this->magnitude();
    return Tuple(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
}

float Tuple::dot(Tuple other) {
    return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
}

Tuple Tuple::cross(Tuple other) {
    return Vector(this->y * other.z - this->z * other.y,
        this->z * other.x - this->x * other.z,
        this->x * other.y - this->y * other.x);
}

std::string Tuple::debugString() {
    std::stringstream stream;

    stream << "Tuple: ";
    stream << x;
    stream << " ";
    stream << y;
    stream << " ";
    stream << z;
    stream << " ";
    stream << w;
    stream << "\n";

    return stream.str();
}

float dot(Tuple lhs, Tuple rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

Tuple cross(Tuple lhs, Tuple rhs) {
    return Vector(lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x);
}

Tuple reflect(Tuple in, Tuple normal) {
    return in - normal * 2 * dot(in, normal);
}