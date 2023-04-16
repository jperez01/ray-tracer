#include "lights/direction_light.h"
#include "core/reflection.h"

#include <math.h>

DirectionalLight::DirectionalLight(Vector3f direction, Color color) {
    m_color = color;
    m_direction = direction;
}

Color DirectionalLight::calculateColorFromDirection(Vector3f &normal, const Vector3f &eye, Shape *shape) {
    Vector3f lightDir = Normalize(-m_direction);
    
    Material material = shape->material;
    Color effectiveColor = m_color * material.color;

    Color ambient = effectiveColor * material.ambient;

    float diffuseIntensity = fmaxf(Dot(lightDir, normal), 0.0);
    Color diffuse = diffuseIntensity * effectiveColor * material.diffuse;

    Vector3f reflectedVector = Reflect(-lightDir, normal);
    float specularIntensity = fmaxf(Dot(reflectedVector, eye), 0.0);
    float factor = powf(specularIntensity, material.shininess);
    Color specular = factor * effectiveColor * material.specular;
    
    return ambient + diffuse + specular;
}