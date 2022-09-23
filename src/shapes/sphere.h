#ifndef RTC_SPHERE
#define RTC_SPHERE

#include "primitives/tuple.h"
#include "primitives/color.h"
#include "primitives/ray.h"
#include "primitives/intersections.h"
#include "primitives/tuple.h"
#include "primitives/matrix.h"
#include "shapes/shape.h"

#include <vector>
#include <optional>

class Sphere : public Shape {
    public:
        Sphere(Tuple center, float radius);
        Sphere(Tuple center, float radius, Color color);
        Sphere(Tuple center, float radius, Color color, Matrix &transform);

        Intersections findIntersection(Ray &givenRay);
        Tuple surfaceNormal(Tuple position);

        inline Tuple center() { return m_center; }
        inline float radius() { return m_radius; }
        inline Color color() { return m_color; }
        inline std::optional<Matrix> transform() { return m_transform; }

    private:
        Tuple m_center;
        float m_radius;
        Color m_color;
        std::optional<Matrix> m_transform;
};

#endif