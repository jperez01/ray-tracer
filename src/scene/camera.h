#ifndef RTC_CAMERA
#define RTC_CAMERA

#include "primitives/ray.h"

class Camera {
    public:
        Camera();
        Camera(float hsize, float vsize, float angle);
        Camera(float hsize, float vsize, float angle, Transform &transform);

        inline float hsize() { return m_hsize; }
        inline float vsize() { return m_vsize; }
        inline float pixelSize() { return m_pixel_size; }
        inline Transform transform() { return m_transform; }

        void setTransform(Transform &transform);

        void calculatePixelSize();
        Ray calculateRayForPixel(float x, float y);

    private:
        float m_hsize;
        float m_vsize;
        float m_field_of_view;
        Transform m_transform;
        float m_pixel_size;
        float m_half_width;
        float m_half_height;
};
#endif