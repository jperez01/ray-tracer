#ifndef RTC_PLANE
#define RTC_PLANE

#include "primitives/tuple.h"
#include "shapes/shape.h"

class Plane : public Shape {
    public:
        Plane();
        Plane(Tuple &point, Tuple &normal);
        Plane(Tuple &point, Tuple &normal, Material &material);
        Plane(Tuple &point, Tuple &normal, Matrix &transform, Material &material);

        Tuple surfaceNormal(Tuple &position);
        void findIntersection(Ray &givenRay, Intersections &results);
        Bounds unitBounds();

        void setTransform(Matrix &matrix);
        void setMaterial(Material &material);

        inline std::optional<Matrix> transform() { return m_transform; }
        inline Material material() { return m_material; }

    private:
        std::optional<Matrix> m_transform;
        Material m_material;
        Tuple m_point;
        Tuple m_normal;
};

#endif