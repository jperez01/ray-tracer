#include "shapes/triangle.h"
#include <cmath>

TriangleMesh::TriangleMesh(glm::mat4 &objectToWorld, int numTriangles, std::vector<int> &newIndices, std::vector<Point> &newPositions,
    std::vector<Vector> &newNormals, std::vector<UV> &newUvs) : nTriangles(numTriangles) {
    nVertices = newPositions.size();
    vertexIndices = std::vector(newIndices);

    positions.resize(newPositions.size());
    normals.resize(newNormals.size());
    uvs.resize(newUvs.size());
    for (int i = 0; i < positions.size(); i++) {
        positions[i] = objectToWorld * newPositions[i];
    }

    for (int i = 0; i < normals.size(); i++) {
        normals[i] = objectToWorld * newNormals[i];
    }

    for (int i = 0; i < uvs.size(); i++) {
        uvs[i] = objectToWorld * newUvs[i];
    }
}

Triangle::Triangle(const glm::mat4 *objectToWorld, const glm::mat4 *worldToObject,
    bool reverseOrientation, std::shared_ptr<TriangleMesh> &mesh, int triNumber) :
        Shape(objectToWorld, worldToObject, reverseOrientation), mesh(mesh) {
        v = &mesh->vertexIndices[3 * triNumber];
    }

void Triangle::calculateInfo() {
    m_e1 = m_vertex2 - m_vertex1;
    m_e2 = m_vertex3 - m_vertex1;
    m_normal = glm::normalize(glm::cross(m_e2, m_e1));
}

Tuple Triangle::surfaceNormal(Tuple &point, Intersection &i) {
    return m_normal;
}

void Triangle::findIntersection(Ray &givenRay, Intersections &solutions) {
    glm::vec4 e1 = mesh->positions[v[1]] - mesh->positions[v[0]];
    glm::vec4 e2 = mesh->positions[v[2]] - mesh->positions[v[1]];

    Vector cross_dir = glm::cross(glm::vec3(givenRay.direction()), glm::vec3(e2));

    float determinant = dot(cross_dir, e1);
    if (fabs(determinant) < 0.0001) return;

    float f = 1.0 / determinant;
    Tuple v1_to_origin = givenRay.origin() - m_vertex1;
    float u = f * dot(v1_to_origin, cross_dir);
    if (u < 0.0 || u > 1.0) return;

    Tuple origin_cross_e1 = cross(v1_to_origin, m_e1);
    float v = f * dot(givenRay.direction(), origin_cross_e1);
    if (v < 0.0 || (u + v) > 1.0) return;

    float t = f * dot(m_e2, origin_cross_e1);
    Intersection result{t, this};
    solutions.add(result);
}