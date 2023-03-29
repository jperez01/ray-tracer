#include "lights/point_light.h"

#include "core/reflection.h"

#include <math.h>

PointLight::PointLight(Color color, Point3f position) {
    m_position = position;
    m_color = color;
}

Color PointLight::calculateColorFromPoint(Vector3f &normal, Point3f &position, const Vector3f &eye, Shape &shape, bool inShadow) {
    Material material = shape.material;
    Vector3f lightDir = m_position - position;
    lightDir = Normalize(lightDir);

    Color materialColor = material.color;
    //if (material.pattern == nullptr) materialColor = material.color;
    //else materialColor = material.pattern->getColorAt(position, shape);

    Color effectiveColor = m_color * materialColor;

    Color ambient = effectiveColor * material.ambient;

    if (inShadow) return ambient;

    float diffuseIntensity = fmaxf(Dot(lightDir, normal), 0.0);
    Color diffuse = diffuseIntensity * effectiveColor * material.diffuse;

    Vector3f reflectedVector = Reflect(-lightDir, normal);
    float specularIntensity = fmaxf(Dot(reflectedVector, eye), 0.0);
    float factor = powf(specularIntensity, material.shininess);
    Color specular = factor * m_color * material.specular;
    
    return ambient + diffuse + specular;
}