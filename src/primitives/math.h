#ifndef RTC_PRIMITIVES_MATH_H
#define RTC_PRIMITIVES_MATH_H
#include <stdlib.h>
#include <cmath>

const float EPSILON = 0.00001;


const float GROUP_INFINITE_BIGNUM = 10e6;

inline bool epsilon_eq(float a, float b) {
    return std::abs(a - b) < EPSILON;
}

#endif