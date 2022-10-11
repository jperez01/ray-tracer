#ifndef RTC_MATERIAL
#define RTC_MATERIAL

class Pattern;
#include "primitives/color.h"
#include "patterns/pattern.h"

static const float VACUUM = 1.0, AIR = 1.00029, WATER = 1.333, GLASS = 1.52, DIAMOND = 2.417;

class Material {
    public:
        Material();
        Material(const Color &color);
        Material(const Color &color, float reflective);
        Material(const Color &color, float ambient, float specular, float diffuse, float shininess);
        Material(const Color &color, float ambient, float specular, float diffuse, float shininess, float reflective);

        inline float ambient() { return m_ambient; }
        inline float specular() { return m_specular; }
        inline float diffuse() { return m_diffuse; }
        inline float shininess() { return m_shininess; }
        inline Color color() { return m_color; }
        inline Pattern* pattern() { return m_pattern; }
        inline float reflective() { return m_reflective; }
        inline float transparency() { return m_transparency; }
        inline float refractiveIndex() { return m_refractive_index; }

        void setAmbient(float ambient);
        void setSpecular(float specular);
        void setDiffuse(float diffuse);
        void setShininess(float shininess);
        void setColor(Color &color);
        void setPattern(Pattern *pattern);
        void setReflective(float reflectiveness);
        void setTransparency(float transparency);
        void setRefractiveIndex(float refractive);

        bool operator==(Material &material);

    private:
        float m_ambient;
        float m_specular;
        float m_diffuse;
        float m_shininess;
        Color m_color;
        Pattern *m_pattern;
        float m_reflective;
        float m_transparency;
        float m_refractive_index;

};
#endif