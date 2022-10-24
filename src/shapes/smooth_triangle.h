#pragma once
#include "shapes/shape.h"

class SmoothTriangle : public Shape {
    public:
        SmoothTriangle();
        SmoothTriangle(Tuple &v1, Tuple &v2, Tuple &v3, Tuple &n1, Tuple &n2, Tuple &n3);
        ~SmoothTriangle() = default;

        void calculateInfo();
        void findIntersection(Ray &givenRay, Intersections &solutions);
        Tuple surfaceNormal(Tuple &point, Intersection &i);
        Bounds unitBounds();

        inline std::optional<Matrix> transform() { return m_transform; }
        inline Material material() { return m_material; }
        inline Tuple v1() { return m_vertex1; }
        inline Tuple v2() { return m_vertex2; }
        inline Tuple v3() { return m_vertex3; }
        inline Tuple n1() { return m_normal1; }
        inline Tuple n2() { return m_normal2; }
        inline Tuple n3() { return m_normal3; }
        inline Tuple e1() { return m_e1; }
        inline Tuple e2() { return m_e2; }

        void setTransform(Matrix &transform);
        void setMaterial(Material &material);

    private:
        Tuple m_vertex1;
        Tuple m_vertex2;
        Tuple m_vertex3;
        Tuple m_normal1;
        Tuple m_normal2;
        Tuple m_normal3;

        std::optional<Matrix> m_transform = std::optional<Matrix>{};
        Material m_material = Material{};
        Tuple m_e1;
        Tuple m_e2;
};