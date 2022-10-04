#include "scene/computations.h"

Computations::Computations(Intersection &hit, Ray &ray) {
    m_time = hit.m_time;
    m_object = hit.m_shape;

    m_point = ray.position(m_time);
    m_eye = -ray.direction();
    m_normal = m_object->surfaceNormal(m_point);
    m_over_point = m_point + m_normal * 0.01;

    if (dot(m_normal, m_eye) < 0.0) {
        m_inside = true;
        m_normal = -m_normal;
    } else m_inside = false;
}