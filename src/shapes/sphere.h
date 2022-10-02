#ifndef RTC_SPHERE
#define RTC_SPHERE

#include "primitives/tuple.h"
#include "shapes/material.h"
#include "primitives/ray.h"
#include "primitives/intersections.h"
#include "primitives/tuple.h"
#include "primitives/matrix.h"
#include "shapes/shape.h"

#include <vector>
#include <optional>

class Sphere : public Shape {
    public:
        Sphere();
        Sphere(Tuple &center, float radius);
        Sphere(const Material &material);
        Sphere(const Material &material, Matrix &transform);
        Sphere(Tuple &center, float radius, const Material &material);
        Sphere(Tuple &center, float radius, const Material &material, Matrix &transform);

        Tuple surfaceNormal(Tuple &position);
        void findIntersection(Ray &givenRay, Intersections &solutions);

        inline Tuple center() { return m_center; }
        inline float radius() { return m_radius; }
        inline Material material() { return m_material; }
        inline std::optional<Matrix> transform() { return m_transform; }

        void setTransform(Matrix &matrix);
        void setMaterial(Material &material);

    private:
        Tuple m_center;
        float m_radius;
        Material m_material;
        std::optional<Matrix> m_transform;
};

void findIntersection(Sphere &sphere, Ray &givenRay, Intersections &solutions);

#endif