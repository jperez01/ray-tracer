#pragma once

#include "primitives/newPrimitives.h"

class Bounds {
    public:
        Bounds();
        Bounds(Point min, Point max);
        ~Bounds() = default;

        void extendTo(Point &point);
        void merge(Bounds &other);
        Point center();

        inline Point max() { return m_max; }
        inline Point min() { return m_min; }

    private:
        Point m_min;
        Point m_max;
};