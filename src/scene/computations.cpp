#include "scene/computations.h"
#include "core/reflection.h"
#include <set>

Computations::Computations(Intersection &hit, Ray &ray) {
    time = hit.m_time;
    object = hit.m_shape;

    point = ray.position(time);
    eye = -ray.direction;
    normal = object->surfaceNormal(point, hit);

    if (Dot(normal, (Vector3f)eye) < 0.0) {
        isInside = true;
        normal = -normal;
    } else isInside = false;

    reflect = Reflect(eye, normal);
    over_point = point + normal * 0.01;
}

Computations::Computations(Intersection &hit, Ray &ray, Intersections &results) {
    time = hit.m_time;
    object = hit.m_shape;

    point = ray.position(time);
    eye = -ray.direction;
    normal = object->globalNormal(point, hit);

    std::vector<Shape*> containers;
    
    for (Intersection &i : results.intersectionsList()) {
        if (i == hit) {
            if (containers.empty()) refract1 = 1.0f;
            else refract1 = containers.back()->material.refractive_index;
        }
        std::vector<Shape*>::iterator it = std::find(containers.begin(), containers.end(), i.m_shape);
        if (it != containers.end()) containers.erase(it);
        else containers.push_back(i.m_shape);

        if (i == hit) {
            if (containers.empty()) refract2 = 1.0f;
            else refract2 = containers.back()->material.refractive_index;
        }
    }

    if (Dot(normal, eye) < 0.0) {
        isInside = true;
        normal = -normal;
    } else isInside = false;

    over_point = point + normal * 0.01;
    under_point = point - normal * 0.01;

    reflect = Reflect(ray.direction, normal);
}