#ifndef RTC_COLOR
#define RTC_COLOR

#include "primitives/tuple.h"

class Color : public Tuple {
    public:
        Color();
        Color(float r, float g, float b);
        ~Color() = default;

        void clamp();

        float r() const { return this->x; }
        float g() const { return this->y; }
        float b() const { return this->z; }

        Color operator+(const Color second);

        Color operator-(const Color second);

        Color operator*(const Color second);

        Color operator*(float mult);
        Color operator+=(const Color second);

};

Color operator*(float mult, Color color);

#endif