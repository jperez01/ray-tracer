#include "newPrimitives.h"

namespace rtutil {

glm::vec4 createPoint(float x, float y, float z) {
    return glm::vec4(x, y, z, 1.0);
}

glm::vec4 createVector(float x, float y, float z) {
    return glm::vec4(x, y, z, 0.0);
}


bool swapsHandedness(const glm::mat4 &matrix) {
    glm::mat3 upperLeft = glm::mat3(matrix);
    return glm::determinant(upperLeft) < 0;
}

bool swapsHandedness(const glm::mat4 *matrix) {
    if (matrix == nullptr) return false;
    
    glm::mat3 upperLeft = glm::mat3(*matrix);
    return glm::determinant(upperLeft) < 0;
}
};