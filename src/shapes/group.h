#pragma once

#include "shapes/shape.h"

class Group : public Shape {
    public:
        Group();
        Group(Matrix transform);
        Group(Material &material);
        void addShape(Shape* shape);
        void findIntersection(Ray &givenRay, Intersections &solutions);
        void checkAxis(float origin, float direction,
            float *tmin, float *tmax, float direction_min, float direction_max);
        Tuple surfaceNormal(Tuple &position, Intersection &i);
        void extendBounds(Shape *shape);
        bool includes(Shape* other);

        void setTransform(Matrix &matrix);
        void setMaterial(Material &material);

        inline std::vector<Shape*> children() { return m_children; }
        inline std::optional<Matrix> transform() { return m_transform; }
        inline Material material() { return m_material; }
        inline Bounds unitBounds() { return m_bounds; }
        inline int size() { return m_children.size(); }

    private:
        std::vector<Shape*> m_children;
        std::optional<Matrix> m_transform;
        Material m_material;
        Bounds m_bounds = Bounds(Point(0,0,0), Point(0,0,0));
};
