#pragma once

#include "primitives/matrix.h"
#include "primitives/tuple.h"

class Bounds {
    public:
        Bounds();
        Bounds(Tuple min, Tuple max);
        ~Bounds() = default;

        void extendTo(Tuple &point);
        void merge(Bounds &other);
        Tuple center();

        inline Tuple max() { return m_max; }
        inline Tuple min() { return m_min; }

    private:
        Tuple m_min;
        Tuple m_max;
};