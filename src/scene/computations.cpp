#include "scene/computations.h"
#include <set>

Computations::Computations(Intersection &hit, Ray &ray) {
    m_time = hit.m_time;
    m_object = hit.m_shape;

    m_point = ray.position(m_time);
    m_eye = -ray.direction();
    m_normal = m_object->surfaceNormal(m_point);
    m_over_point = m_point + m_normal * 0.01;

    m_reflect = reflect(ray.direction(), m_normal);

    if (dot(m_normal, m_eye) < 0.0) {
        m_inside = true;
        m_normal = -m_normal;
    } else m_inside = false;
}

Computations::Computations(Intersection &hit, Ray &ray, Intersections &results) {
    m_time = hit.m_time;
    m_object = hit.m_shape;

    m_point = ray.position(m_time);
    m_eye = -ray.direction();
    m_normal = m_object->surfaceNormal(m_point);
    m_over_point = m_point + m_normal * 0.01;
    m_under_point = m_point - m_normal * 0.01;

    m_reflect = reflect(ray.direction(), m_normal);

    std::vector<Shape*> containers;
    
    for (Intersection &i : results.intersectionsList()) {
        if (i == hit) {
            if (containers.empty()) m_refract1 = 1.0;
            else m_refract1 = containers.back()->material().refractiveIndex();
        }
        std::vector<Shape*>::iterator it = std::find(containers.begin(), containers.end(), i.m_shape);
        if (it != containers.end()) containers.erase(it);
        else containers.push_back(i.m_shape);

        if (i == hit) {
            if (containers.empty()) m_refract2 = 1.0;
            else m_refract2 = containers.back()->material().refractiveIndex();
        }
    }

    if (dot(m_normal, m_eye) < 0.0) {
        m_inside = true;
        m_normal = -m_normal;
    } else m_inside = false;
}