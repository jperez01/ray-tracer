#include "lights/point_light.h"
#include "primitives/color.h"
#include "primitives/tuple.h"

#include <math.h>

PointLight::PointLight(Color color, Tuple position) {
    m_position = position;
    m_color = color;
}

Color calculateColorFromPoint(PointLight light, Tuple normal, Tuple position, Shape *shape) {
    Tuple lightDir = light.position() - position;
    lightDir = lightDir.normalized();

    float intensity = fmaxf(dot(lightDir, normal), 0.0);
    return light.color() * intensity * shape->color();
}