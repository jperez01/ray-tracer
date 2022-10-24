#include "shapes/cylinder.h"
#include <cmath>

Cylinder::Cylinder() :
    m_transform(std::optional<Matrix>{}),
    m_material(Material{}),
    m_minimum(-INFINITY),
    m_maximum(INFINITY),
    m_closed(true) {}

Cylinder::Cylinder(Matrix &transform, Material &material) {
    m_material = material;
    m_transform = std::optional<Matrix>{transform};
    m_minimum = -INFINITY;
    m_maximum = INFINITY;
    m_closed = true;
}

Cylinder::Cylinder(float min, float max) :
    m_minimum(min),
    m_maximum(max),
    m_material(Material{}),
    m_transform(std::optional<Matrix>{}),
    m_closed(true) {}

Cylinder::Cylinder(float min, float max, Matrix &transform, Material &material) {
    m_material = material;
    m_transform = std::optional<Matrix>{transform};
    m_minimum = min;
    m_maximum = max;
    m_closed = true;
}

void Cylinder::findIntersection(Ray &givenRay, Intersections &solutions) {
    Ray ray;
    if (m_transform.has_value()) {
        Matrix inverse = m_transform.value().inverse();
        ray = transformRay(givenRay, inverse);
    } else ray = givenRay;

    float a = ray.direction().x * ray.direction().x 
        + ray.direction().z * ray.direction().z;

    if (a > 0.000001) {
        float b = 2 * ray.origin().x * ray.direction().x
        + 2 * ray.origin().z * ray.direction().z;
        float c = ray.origin().x * ray.origin().x
            + ray.origin().z * ray.origin().z - 1;
        
        float discriminant = b * b - (4 * a * c);
        if (discriminant < 0.0) return;

        float two_a = 2 * a;
        float sqrt_dis = sqrt(discriminant);

        float t0 = (-b + sqrt_dis) / two_a;
        float t1 = (-b - sqrt_dis) / two_a;
        if (t0 > t1) {
            float temp = t0;
            t0 = t1;
            t1 = temp;
        }

        float y0 = ray.origin().y + t0 * ray.direction().y;
        if (m_minimum < y0 && y0 < m_maximum) {
            Intersection inter0(t0);
            solutions.add(inter0);
        }

        float y1 = ray.origin().y + t1 * ray.direction().y;
        if (m_minimum < y1 && y1 < m_maximum) {
            Intersection inter1(t1);
            solutions.add(inter1);
        }
    }

    intersectCaps(ray, solutions);
}

void Cylinder::intersectCaps(Ray &ray, Intersections &solutions) {
    if (!m_closed || ray.direction().y < 0.0001) return;

    float t = (m_minimum - ray.origin().y) / ray.direction().y;
    if (hasCap(ray, t)) {
        Intersection inter(t);
        solutions.add(inter);
    }

    float t2 = (m_maximum - ray.origin().y) / ray.direction().y;
    if (hasCap(ray, t2)) {
        Intersection inter(t2);
        solutions.add(inter);
    }
}

bool hasCap(Ray &ray, float t) {
    float x = ray.origin().x + t * ray.direction().x;
    float z = ray.origin().z + t * ray.direction().z;
    float value = x * x + z * z;

    return value <= 1.0;
}

void Cylinder::setTransform(Matrix &transform) {
    m_transform = std::optional<Matrix>{transform};
}

void Cylinder::setMaterial(Material &material) {
    m_material = material;
}

void Cylinder::setClosed(bool is_closed) {
    m_closed = is_closed;
}

Tuple Cylinder::surfaceNormal(Tuple &position, Intersection &i) {
    float distance = position.x * position.x + position.z * position.z;

    if (distance < 1 && position.y >= m_maximum - 0.00001) return Vector(0, 1, 0);
    else if (distance < 1 && position.y <= m_minimum + 0.00001) return Vector(0, -1, 0);
    
    return Vector(position.x, 0, position.z);
}

Bounds Cylinder::unitBounds() {
    float xmax = 1, ymax = INFINITY, zmax = 1;
    if (m_maximum != INFINITY) ymax = m_maximum;

    float xmin = -1, ymin = -INFINITY, zmin = -1;
    if (m_minimum != INFINITY) ymin = m_minimum;

    return Bounds(Point(xmin, ymin, zmin), Point(xmax, ymax, zmax));
}