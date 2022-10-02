#include "scene/computations.h"

Computations::Computations(Intersection &hit, Ray &ray) {
    m_time = hit.m_time;
    m_object = hit.m_shape;

    std::string originInfo = ray.debugString();
    printf("%s \n", originInfo.c_str());

    std::string info = hit.m_ray.debugString();
    printf("%s \n", info.c_str());

    m_point = hit.m_ray.position(m_time);
    m_eye = -hit.m_ray.direction();
    m_normal = m_object->surfaceNormal(m_point);

    if (dot(m_normal, m_eye) < 0.0) {
        m_inside = true;
        m_normal = -m_normal;
    } else m_inside = false;
}