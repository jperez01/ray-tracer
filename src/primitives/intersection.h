#ifndef RTC_INTER
#define RTC_INTER

#include "shapes/shape.h"
#include "tuple.h"

class Intersection {
    public:
        Intersection(float time, Shape* shape);

        inline float time() { return m_time; }
        inline Shape* shape() { return m_shape; }

    private:
        float m_time;
        Shape* m_shape;
};

#endif