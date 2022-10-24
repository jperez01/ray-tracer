#pragma once

#include "shapes/shape.h"

class Cylinder : public Shape {
    public:
        Cylinder();
        Cylinder(Matrix &transform, Material &material);
        Cylinder(float min, float max);
        Cylinder(float min, float max, Matrix &transform, Material &material);
        
        void findIntersection(Ray &givenRay, Intersections &solutions);
        void intersectCaps(Ray &ray, Intersections &solutions);
        Tuple surfaceNormal(Tuple &position, Intersection &i);
        Bounds unitBounds();

        inline std::optional<Matrix> transform() { return m_transform; }
        inline Material material() { return m_material; }

        void setTransform(Matrix &transform);
        void setMaterial(Material &material);
        void setClosed(bool is_closed);

    private:
        std::optional<Matrix> m_transform;
        Material m_material;
        float m_minimum;
        float m_maximum;
        bool m_closed;
};

bool hasCap(Ray &ray, float t);