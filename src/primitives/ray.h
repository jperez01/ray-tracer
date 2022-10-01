#ifndef RTC_RAY
#define RTC_RAY

#include "primitives/tuple.h"
#include "primitives/matrix.h"
#include <string>

class Ray {

    public:
        Ray();
        Ray(Tuple origin, Tuple direction);

        Tuple position(float time);
        std::string debugString();

        inline Tuple origin() { return m_origin; }
        inline Tuple direction() { return m_direction; }
    
    private:
        Tuple m_origin;
        Tuple m_direction;
};

Ray transformRay(Ray &ray, Matrix &matrix);

#endif