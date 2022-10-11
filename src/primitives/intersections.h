#ifndef RTC_INTERS
#define RTC_INTERS

#include <vector>
#include <optional>

class Shape;
#include "shapes/shape.h"

struct Intersection {
    float m_time;
    Shape *m_shape;
    Ray m_ray;

    Intersection() : m_time(-1.0), m_shape(nullptr) {}
    Intersection(float time) : m_time(time), m_shape(nullptr)  {}
    Intersection(float time, Shape *shape) : m_time(time), m_shape(shape) {}
    Intersection(float time, Shape *shape, Ray ray) : m_time(time), m_shape(shape), m_ray(ray) {}

    bool operator==(Intersection other) {
        return other.m_time == this->m_time && other.m_shape == this->m_shape;
    }
};

class Intersections {
    public:
        Intersections();
        Intersections(std::vector<Intersection> &intersections);
        Intersection hit();
        std::optional<Intersection> hitOptional();
        int size();
        void add(Intersection &intersection);
        void sortIntersections();
        inline std::vector<Intersection> intersectionsList() { return m_intersections; }
        Intersection operator[](int index);

    private:
        std::vector<Intersection> m_intersections;
};

#endif