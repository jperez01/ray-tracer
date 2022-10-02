#include "scene/camera.h"
#include <cmath>

Camera::Camera() :
 m_hsize(1.0), 
 m_vsize(1.0), 
 m_field_of_view(1.0), 
 m_transform(identityMatrix(4)) {
    calculatePixelSize();
 }

Camera::Camera(float hsize, float vsize, float angle) :
 m_hsize(hsize), 
 m_vsize(vsize), 
 m_field_of_view(angle), 
 m_transform(identityMatrix(4)) {
    calculatePixelSize();
 }

Camera::Camera(float hsize, float vsize, float angle, Matrix &transform) :
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

void Camera::setTransform(Matrix &transform) {
    m_transform = transform;
}

Ray Camera::calculateRayForPixel(float x, float y) {
    float xoffset = (x + 0.5) * m_pixel_size;
    float yoffset = (y + 0.5) * m_pixel_size;

    float world_x = m_half_width - xoffset;
    float world_y = m_half_height - yoffset;

    Matrix inverseTransform = m_transform.inverse();
    Tuple pixel = inverseTransform * Point(world_x, world_y, -1.0);
    Tuple origin = inverseTransform * Point(0, 0, 0);
    Tuple direction = (pixel - origin).normalized();

    return Ray(origin, direction);
}