#include "materials/material.h"
#include "primitives/color.h"
#include "primitives/math.h"

Material::Material() : 
    color(Color(1.0, 1.0, 1.0)), 
    ambient(0.1), 
    diffuse(0.9), 
    specular(0.9), 
    shininess(200.0),
    pattern(nullptr),
    reflective(false),
    transparency(0.0),
    refractive_index(VACUUM) {}

bool Material::operator==(Material &material) {
    return this->color == material.color
    && epsilon_eq(this->ambient, material.ambient)
    && epsilon_eq(this->diffuse, material.diffuse)
    && epsilon_eq(this->specular, material.specular)
    && epsilon_eq(this->shininess, material.shininess);
}