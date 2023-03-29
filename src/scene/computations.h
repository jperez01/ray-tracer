#ifndef RTC_COMPUTATIONS
#define RTC_COMPUTATIONS

#include "primitives/intersections.h"

class Computations {
    public:
        Computations(Intersection &hit, Ray &ray);
        Computations(Intersection &hit, Ray &ray, Intersections &results);

        float time, refract1, refract2;
        Shape* object;
        bool isInside;

        Point3f point, over_point, under_point;
        Vector3f eye, normal, reflect;
};

#endif