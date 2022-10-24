#pragma once
#include "shapes/shape.h"

class Triangle : public Shape {
    public:
        Triangle();
        Triangle(Tuple &v1, Tuple &v2, Tuple &v3);
        Triangle(Tuple &v1, Tuple &v2, Tuple &v3, Material material);
        Triangle(Tuple &v1, Tuple &v2, Tuple &v3, Material material, Matrix transform);
        ~Triangle() = default;

        void calculateInfo();
        void findIntersection(Ray &givenRay, Intersections &solutions);
        Tuple surfaceNormal(Tuple &point, Intersection &i);
        Bounds unitBounds();

        inline std::optional<Matrix> transform() { return m_transform; }
        inline Material material() { return m_material; }
        inline Tuple v1() { return m_vertex1; }
        inline Tuple v2() { return m_vertex2; }
        inline Tuple v3() { return m_vertex3; }
        inline Tuple normal() { return m_normal; }
        inline Tuple e1() { return m_e1; }
        inline Tuple e2() { return m_e2; }

        void setTransform(Matrix &transform);
        void setMaterial(Material &material);

    private:
        Tuple m_vertex1;
        Tuple m_vertex2;
        Tuple m_vertex3;
        std::optional<Matrix> m_transform = std::optional<Matrix>{};
        Material m_material = Material{};
        Tuple m_e1;
        Tuple m_e2;
        Tuple m_normal;
};