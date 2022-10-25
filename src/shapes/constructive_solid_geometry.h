#pragma once

#include "shapes/shape.h"
#include <vector>

class IntersectionStrategy {
    public:
    ~IntersectionStrategy() = default;

    virtual bool intersectionAllowed(bool left_hit, bool in_left, bool in_right) = 0;
};

class UnionStrategy : public IntersectionStrategy {
    public:
        UnionStrategy() {};
        ~UnionStrategy() = default;

        bool intersectionAllowed(bool left_hit, bool in_left, bool in_right) {
            return (left_hit && !in_right) || (!left_hit && !in_left);
        }
};

class IntersectStrategy : public IntersectionStrategy {
    public:
        IntersectStrategy() {};
        ~IntersectStrategy() = default;

        bool intersectionAllowed(bool left_hit, bool in_left, bool in_right) {
            return (left_hit && in_right) || (!left_hit && in_left);
        }
};

class DifferenceStrategy : public IntersectionStrategy {
    public:
        DifferenceStrategy() {};
        ~DifferenceStrategy() = default;

        bool intersectionAllowed(bool left_hit, bool in_left, bool in_right) {
            return (left_hit && !in_right) || (!left_hit && in_left);
        }
};

class ConstructiveSolidGeometry : public Shape {
    public:
        ConstructiveSolidGeometry(Shape *left, Shape *right,
            IntersectionStrategy *strategy);
        ~ConstructiveSolidGeometry() = default;

        Tuple surfaceNormal(Tuple &position, Intersection &i);
        void findIntersection(Ray &ray, Intersections &solutions);

        Intersections filterIntersections(Intersections &solutions);

        Bounds unitBounds();
        bool includes(Shape *other);

        inline Shape* left() { return m_left; }
        inline Shape* right() { return m_right; }

    private:
        Shape *m_right;
        Shape *m_left;
        IntersectionStrategy *m_strategy;
};