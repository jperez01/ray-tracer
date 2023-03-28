#pragma once
#include "shapes/shape.h"
#include <memory>

struct TriangleMesh {
    TriangleMesh(glm::mat4 &objectToWorld, int numTriangles, std::vector<int> &newIndices, std::vector<Point> &newPositions,
        std::vector<Vector> &newNormals, std::vector<UV> &newUvs);

    int nTriangles, nVertices;

    std::vector<int> vertexIndices;
    std::vector<Point> positions;
    std::vector<Vector> normals;
    std::vector<UV> uvs;
};

class Triangle : public Shape {
    public:
        Triangle(const glm::mat4 *objectToWorld, const glm::mat4 *worldToObject,
            bool reverseOrientation, std::shared_ptr<TriangleMesh> &mesh, int triNumber);
        ~Triangle() = default;

        void calculateInfo();
        void findIntersection(Ray &givenRay, Intersections &solutions);
        Vector surfaceNormal(Point &position, Intersection &i);
        Bounds unitBounds();

    private:
        std::shared_ptr<TriangleMesh> mesh;
        const int *v;
};