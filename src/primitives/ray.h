#ifndef RTC_RAY
#define RTC_RAY

#include "core/transform.h"
#include <string>

using pbrt::Transform;
using pbrt::Point3f;
using pbrt::Vector3f;

class Ray {

    public:
        Ray();
        Ray(Point3f origin, Vector3f direction);

        Point3f position(float time);
        std::string debugString();

        Point3f origin;
        Vector3f direction;
};

Ray transformRay(Ray &ray, Transform &matrix);

#endif