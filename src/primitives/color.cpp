#include "color.h"

Color::Color() : Tuple(0, 0, 0, 0) {}

Color::Color(float r, float g, float b) : Tuple(r, g, b, 0) {}

Color Color::operator+(const Color second) {
    return Color(this->r() + second.r(), this->g() + second.g(), this->b() + second.b());
}

Color Color::operator-(const Color second) {
    return Color(this->r() - second.r(), this->g() - second.g(), this->b() - second.b());
}

Color Color::operator*(const Color second) {
    return Color(this->r() * second.r(), this->g() * second.g(), this->b() * second.b());
}

Color Color::operator*(float mult) {
    return Color(this->r() * mult, this->g() * mult, this->b() * mult);
}

Color Color::operator+=(const Color second) {
    return Color(this->r() + second.r(), this->g() + second.g(), this->b() + second.b());
}