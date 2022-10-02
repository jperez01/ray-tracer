#ifndef RTC_TUPLE
#define RTC_TUPLE

#include <string>

class Tuple {
    public:
        float x;
        float y;
        float z;
        float w;

        Tuple();
        Tuple(float v1, float v2, float v3);
        Tuple(float v1, float v2, float v3, float v4);

        Tuple operator+(const Tuple second);

        Tuple operator-(const Tuple second);

        Tuple operator-();

        Tuple operator*(float mult);

        Tuple operator/(float mult);

        bool operator==(const Tuple other);

        bool isPoint();
        bool isVector();

        float dot(Tuple other);
        Tuple cross(Tuple other);

        float magnitude();
        Tuple normalized();

        std::string debugString();
};

Tuple Point(float x, float y, float z);
Tuple Vector(float x, float y, float z);

float dot(Tuple lhs, Tuple rhs);
Tuple cross(Tuple lhs, Tuple rhs);
Tuple reflect(Tuple in, Tuple normal);

#endif