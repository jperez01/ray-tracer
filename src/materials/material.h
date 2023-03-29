#pragma once

#include "patterns/pattern.h"

static const float VACUUM = 1.0, AIR = 1.00029, WATER = 1.333, GLASS = 1.52, DIAMOND = 2.417;

class Material {
public:
    Material();
    bool operator==(Material &material);

    Color color;
    Pattern *pattern;

    float reflective, transparency, refractive_index;
    float ambient, specular, diffuse, shininess;
};