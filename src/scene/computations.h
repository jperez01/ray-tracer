#ifndef RTC_COMPUTATIONS
#define RTC_COMPUTATIONS

#include "shapes/shape.h"
#include "primitives/tuple.h"
#include "primitives/ray.h"
#include "primitives/intersections.h"

class Computations {
    public:
        Computations(Intersection &hit, Ray &ray);
        Computations(Intersection &hit, Ray &ray, Intersections &results);

        inline float time() { return m_time; }
        inline Shape* object() { return m_object; }
        inline Tuple point() { return m_point; }
        inline Tuple eye() { return m_eye; }
        inline Tuple normal() { return m_normal; }
        inline Tuple reflectv() { return m_reflect; }
        inline bool isInside() { return m_inside; }
        inline Tuple overPoint() { return m_over_point; }
        inline Tuple underPoint() { return m_under_point; }
        inline float refract1() { return m_refract1; }
        inline float refract2() { return m_refract2; }

    private:
        float m_time;
        Shape* m_object;
        Tuple m_point;
        Tuple m_eye;
        Tuple m_normal;
        Tuple m_over_point;
        Tuple m_under_point;
        Tuple m_reflect;
        bool m_inside;
        float m_refract1;
        float m_refract2;
};

#endif