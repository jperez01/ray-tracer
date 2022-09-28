#include "shapes/material.h"
#include "primitives/color.h"

Material::Material() : 
    m_color(Color(1.0, 1.0, 1.0)), 
    m_ambient(1.0), 
    m_diffuse(1.0), 
    m_specular(1.0), 
    m_shininess(1.0) {}

Material::Material(const Color &color) : 
    m_color(color),
    m_ambient(1.0),
    m_diffuse(1.0),
    m_specular(1.0),
    m_shininess(1.0) {}

Material::Material(const Color &color, float ambient, float diffuse, float specular, float shininess) : 
    m_color(color),
    m_ambient(ambient),
    m_diffuse(diffuse),
    m_specular(specular),
    m_shininess(shininess) {}

