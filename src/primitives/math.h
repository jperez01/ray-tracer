#ifndef RTC_PRIMITIVES_MATH_H
#define RTC_PRIMITIVES_MATH_H
#include <stdlib.h>

const float EPSILON = 0.00001;

inline bool epsilon_eq(float a, float b) {
    return abs(a - b) < EPSILON;
}

#endif