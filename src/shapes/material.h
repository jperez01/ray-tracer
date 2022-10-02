#ifndef RTC_MATERIAL
#define RTC_MATERIAL

#include "primitives/color.h"

class Material {
    public:
        Material();
        Material(const Color &color);
        Material(const Color &color, float ambient, float specular, float diffuse, float shininess);

        inline float ambient() { return m_ambient; }
        inline float specular() { return m_specular; }
        inline float diffuse() { return m_diffuse; }
        inline float shininess() { return m_shininess; }
        inline Color color() { return m_color; }

        void setAmbient(float ambient);
        void setSpecular(float specular);
        void setDiffuse(float diffuse);
        void setShininess(float shininess);
        void setColor(Color &color);

        bool operator==(Material &material);

    private:
        float m_ambient;
        float m_specular;
        float m_diffuse;
        float m_shininess;
        Color m_color;

};

#endif