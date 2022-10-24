#pragma once

#include "shapes/shape.h"

class Cube : public Shape {
    public:
        Cube();
        Cube(Matrix &transform, Material &material);

        void findIntersection(Ray &givenRay, Intersections &solutions);
        void checkAxis(float origin, float direction, std::vector<float> &solutions);
        Tuple surfaceNormal(Tuple &position, Intersection &i);

        inline std::optional<Matrix> transform() { return m_transform; }
        inline Material material() { return m_material; }

        void setTransform(Matrix &transform);
        void setMaterial(Material &material);

    private:
        std::optional<Matrix> m_transform;
        Material m_material;
};