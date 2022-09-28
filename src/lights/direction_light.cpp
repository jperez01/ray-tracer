#include "lights/direction_light.h"
#include "primitives/color.h"

#include <math.h>

DirectionalLight::DirectionalLight(Tuple direction, Color color) {
    m_color = color;
    m_direction = direction;
}

Color calculateColorFromDirection(DirectionalLight &light, Tuple &normal, const Tuple &eye, Shape *shape) {
    Tuple lightDir = -light.direction();
    lightDir = lightDir.normalized();
    
    Material material = shape->material();
    Color effectiveColor = light.color() * material.color();

    Color ambient = effectiveColor * material.ambient();

    float diffuseIntensity = fmaxf(dot(lightDir, normal), 0.0);
    Color diffuse = diffuseIntensity * effectiveColor * material.diffuse();

    Tuple reflectedVector = reflect(-lightDir, normal);
    float specularIntensity = fmaxf(dot(reflectedVector, eye), 0.0);
    float factor = powf(specularIntensity, material.shininess());
    Color specular = factor * effectiveColor * material.specular();
    
    return ambient + diffuse + specular;
}