#include "scene/camera.h"
#include <cmath>

Camera::Camera() :
 m_hsize(1.0), 
 m_vsize(1.0), 
 m_field_of_view(1.0), 
 m_transform(pbrt::Translate(Vector3f(0, 0, 0))) {
    calculatePixelSize();
 }

Camera::Camera(float hsize, float vsize, float angle) :
 m_hsize(hsize), 
 m_vsize(vsize), 
 m_field_of_view(angle), 
 m_transform(pbrt::Translate(Vector3f(0, 0, 0))) {
    calculatePixelSize();
 }

Camera::Camera(float hsize, float vsize, float angle, Transform &transform) :
 m_hsize(hsize), 
 m_vsize(vsize), 
 m_field_of_view(angle), 
 m_transform(transform) {
    calculatePixelSize();
 }

void Camera::calculatePixelSize() {
    float half_view = tan(m_field_of_view / 2);
    float aspect = m_hsize / m_vsize;

    if (aspect >= 1) {
        m_half_height = half_view / aspect;
        m_half_width = half_view;
    } else {
        m_half_height = half_view;
        m_half_width = half_view * aspect;
    }

    m_pixel_size = m_half_width * 2 / m_hsize;
}

void Camera::setTransform(Transform &transform) {
    m_transform = transform;
}

Ray Camera::calculateRayForPixel(float x, float y) {
    float xoffset = (x + 0.5) * m_pixel_size;
    float yoffset = (y + 0.5) * m_pixel_size;

    float world_x = m_half_width - xoffset;
    float world_y = m_half_height - yoffset;

    Transform inverseTransform = m_transform.GetInverseMatrix();
    Point3f pixel = inverseTransform(Point3f(world_x, world_y, -1.0));
    Point3f origin = inverseTransform(Point3f(0, 0, 0));
    Vector3f direction = Normalize(pixel - origin);

    Ray newRay(origin, direction);
    return newRay;
}