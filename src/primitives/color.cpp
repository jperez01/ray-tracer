#include "color.h"

Color::Color() : Tuple(0, 0, 0, 0) {}

Color::Color(float r, float g, float b) : Tuple(r, g, b, 0) {}

void Color::clamp() {
    if (x < 0.0f) x = 0.0f;
    else if (x > 1.0f) x = 1.0f;

    if (y < 0.0f) y = 0.0f;
    else if (y > 1.0f) y = 1.0f;

    if (z < 0.0f) z = 0.0f;
    else if (z > 1.0f) z = 1.0f;
}

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

Color operator*(float mult, Color color) {
    return Color(color.r() * mult, color.g() * mult, color.b() * mult);
}