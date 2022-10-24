#include "shapes/cube.h"
#include "primitives/math.h"
#include <limits>
#include <algorithm>

Cube::Cube() :
    m_transform(std::optional<Matrix>{}),
    m_material(Material{}) {}

Cube::Cube(Matrix &transform, Material &material) :
    m_material(material) {
        m_transform = std::optional<Matrix>{transform};
    }

void Cube::findIntersection(Ray &givenRay, Intersections &solutions) {
    Ray ray;
    if (this->transform().has_value()) {
        Matrix inverse = this->transform().value();
        ray = transformRay(givenRay, inverse);
    } ray = givenRay;

    std::vector<float> minsAndMaxes;
    checkAxis(ray.origin().x, ray.direction().x, minsAndMaxes);
    checkAxis(ray.origin().y, ray.direction().y, minsAndMaxes);
    checkAxis(ray.origin().z, ray.direction().z, minsAndMaxes);

    float tmin = std::max({minsAndMaxes[0], minsAndMaxes[2], minsAndMaxes[4]});
    float tmax = std::min({minsAndMaxes[1], minsAndMaxes[3], minsAndMaxes[5]});

    Intersection min(tmin);
    Intersection max(tmax);

    if (tmin <= tmax) {
        solutions.add(min);
        solutions.add(max);
    }
}

void Cube::checkAxis(float origin, float direction, std::vector<float> &solutions) {
    float tmin_numerator = -1 - origin;
    float tmax_numerator = 1 - origin;

    float tmin, tmax;
    if (abs(direction) >= EPSILON) {
        tmin = tmin_numerator / direction;
        tmax = tmax_numerator / direction;
    } else {
        tmin = tmin_numerator * std::numeric_limits<float>::infinity();
        tmax = tmax_numerator * std::numeric_limits<float>::infinity();
    }

    if (tmin > tmax) {
        solutions.push_back(tmax);
        solutions.push_back(tmin);
    } else {
        solutions.push_back(tmin);
        solutions.push_back(tmax);
    }
}

void Cube::setTransform(Matrix &transform) {
    m_transform = std::optional<Matrix>{transform};
}

void Cube::setMaterial(Material &material) {
    m_material = material;
}

Tuple Cube::surfaceNormal(Tuple &point, Intersection &i) {
    float absx = abs(point.x), absy = abs(point.y), absz = abs(point.z);
    float maxc = std::max({absx, absy, absz});

    if (maxc == absx) return Vector(point.x, 0, 0);
    else if (maxc == absy) return Vector(0, point.y, 0);
    else return Vector(0, 0, point.z);
}