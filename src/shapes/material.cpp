#include "shapes/material.h"
#include "primitives/color.h"
#include "primitives/math.h"

Material::Material() : 
    m_color(Color(1.0, 1.0, 1.0)), 
    m_ambient(0.1), 
    m_diffuse(0.9), 
    m_specular(0.9), 
    m_shininess(200.0) {}

Material::Material(const Color &color) : 
    m_color(color),
    m_ambient(0.1),
    m_diffuse(0.9),
    m_specular(0.9),
    m_shininess(200.0) {}

Material::Material(const Color &color, float ambient, float diffuse, float specular, float shininess) : 
    m_color(color),
    m_ambient(ambient),
    m_diffuse(diffuse),
    m_specular(specular),
    m_shininess(shininess) {}

void Material::setAmbient(float ambient) { m_ambient = ambient; }
void Material::setSpecular(float specular) { m_specular = specular; }
void Material::setDiffuse(float diffuse) { m_diffuse = diffuse; }
void Material::setShininess(float shininess) { m_shininess = shininess; }
void Material::setColor(Color &color) { m_color = color; }

bool Material::operator==(Material &material) {
    return this->color() == material.color()
    && epsilon_eq(this->ambient(), material.ambient())
    && epsilon_eq(this->diffuse(), material.diffuse())
    && epsilon_eq(this->specular(), material.specular())
    && epsilon_eq(this->shininess(), material.shininess());
}