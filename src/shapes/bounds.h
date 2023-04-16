#ifndef RTC_BOUNDS
#define RTC_BOUNDS

#include "core/geometry.h"
using pbrt::Point3f;
using pbrt::Vector3f;

class Bounds {
    public:
        Bounds();
        Bounds(Point3f min, Point3f max);
        ~Bounds() = default;

        void extendTo(Point3f &point);
        void merge(Bounds &other);
        Point3f center();

        inline Point3f max() { return m_max; }
        inline Point3f min() { return m_min; }

    private:
        Point3f m_min;
        Point3f m_max;
};

#endif