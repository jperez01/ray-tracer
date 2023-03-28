#pragma once

#include <glm/glm.hpp>

namespace rtutil {
    glm::vec4 createPoint(float x, float y, float z);
    glm::vec4 createVector(float x, float y, float z);

    bool swapsHandedness(const glm::mat4 &matrix);
    bool swapsHandedness(const glm::mat4 *matrix);
};

using Point = glm::vec4;
using Vector = glm::vec4;
using UV = glm::vec2;