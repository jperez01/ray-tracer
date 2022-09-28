#include "lights/point_light.h"
#include "primitives/color.h"
#include "primitives/tuple.h"

#include <math.h>

PointLight::PointLight(Color color, Tuple position) {
    m_position = position;
    m_color = color;
}

Color calculateColorFromPoint(PointLight &light, Tuple &normal, Tuple &position, const Tuple &eye, Shape *shape) {
    Tuple lightDir = light.position() - position;
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