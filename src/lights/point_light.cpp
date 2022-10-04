#include "lights/point_light.h"
#include "primitives/color.h"
#include "primitives/tuple.h"

#include <math.h>

PointLight::PointLight(Color color, Tuple position) {
    m_position = position;
    m_color = color;
}

Color calculateColorFromPoint(PointLight &light, Tuple &normal, Tuple &position, const Tuple &eye, Material& material) {
    Tuple lightDir = light.position() - position;
    lightDir = lightDir.normalized();

    Color effectiveColor = light.color() * material.color();

    Color ambient = effectiveColor * material.ambient();

    float diffuseIntensity = fmaxf(dot(lightDir, normal), 0.0);
    Color diffuse = diffuseIntensity * effectiveColor * material.diffuse();

    Tuple reflectedVector = reflect(-lightDir, normal).normalized();
    float specularIntensity = fmaxf(dot(reflectedVector, eye), 0.0);
    float factor = powf(specularIntensity, material.shininess());
    Color specular = factor * light.color() * material.specular();
    
    return ambient + diffuse + specular;
}

Color calculateColorFromPoint(PointLight &light, Tuple &normal, Tuple &position, const Tuple &eye, Material &material, bool inShadow) {
    Tuple lightDir = light.position() - position;
    lightDir = lightDir.normalized();

    Color effectiveColor = light.color() * material.color();

    Color ambient = effectiveColor * material.ambient();

    if (inShadow) return ambient;

    float diffuseIntensity = fmaxf(dot(lightDir, normal), 0.0);
    Color diffuse = diffuseIntensity * effectiveColor * material.diffuse();

    Tuple reflectedVector = reflect(-lightDir, normal).normalized();
    float specularIntensity = fmaxf(dot(reflectedVector, eye), 0.0);
    float factor = powf(specularIntensity, material.shininess());
    Color specular = factor * light.color() * material.specular();
    
    return ambient + diffuse + specular;
}