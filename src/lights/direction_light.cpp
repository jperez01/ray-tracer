#include "lights/direction_light.h"
#include "primitives/color.h"

#include <math.h>

DirectionalLight::DirectionalLight(Tuple direction, Color color) {
    m_color = color;
    m_direction = direction;
}

Color calculateColorFromDirection(DirectionalLight light, Tuple normal, Shape *shape) {
    Tuple direction = -light.direction();
    float intensity = fmaxf(dot(direction, normal), 0.0);

    return light.color() * intensity * shape->color();
}