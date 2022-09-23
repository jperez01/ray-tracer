#ifndef RTC_INTERS
#define RTC_INTERS

#include <vector>
#include <optional>
#include "primitives/intersection.h"

class Intersections {
    public:
        Intersections(std::vector<Intersection> intersections);
        std::optional<Intersection> hit();
        int size();
        Intersection operator[](int index);

    private:
        std::vector<Intersection> m_intersections;
};

#endif