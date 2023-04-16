#pragma once

#include "shapes/shape.h"

class Group : public Shape {
    public:
        Group(const Transform *objectToWorld, const Transform *worldToObject,
            bool reverseOrientation);
        void addShape(Shape* shape);
        void findIntersection(Ray &givenRay, Intersections &solutions);
        void checkAxis(float origin, float direction,
            float *tmin, float *tmax, float direction_min, float direction_max);
        Vector3f surfaceNormal(Vector3f &position, Intersection &i);
        void extendBounds(Shape *shape);
        bool includes(Shape* other);

        inline std::vector<Shape*> children() { return m_children; }
        inline Bounds unitBounds() { return m_bounds; }
        inline int size() { return m_children.size(); }

    private:
        std::vector<Shape*> m_children;
        Bounds m_bounds = Bounds(Point3f(0,0,0), Point3f(0,0,0));
};
