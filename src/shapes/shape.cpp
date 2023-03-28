#include "shapes/shape.h"

using namespace rtutil;

Shape::Shape(const glm::mat4 *objectToWorld, const glm::mat4 *worldToObject,
    bool reverseOrientation) :
    objectToWorld(objectToWorld), worldToObject(worldToObject),
    reverseOrientation(reverseOrientation),
    transformSwapsHandedness(swapsHandedness(objectToWorld)) {
        material = Material();
    }

Vector Shape::globalNormal(Point &position, Intersection &i) {
    Shape* shape = this;
    Point local_point = convertWorldToObject(shape, position);
    Vector local_normal = shape->surfaceNormal(local_point, i);

    return normalToWorld(shape, local_normal);
}

bool Shape::includes(Shape *other) {
    return this == other;
}

Point convertWorldToObject(Shape* &shape, Point &point) {
    Point resultPoint;
    if (shape->parent() != nullptr) {
        Shape *parent = shape->parent();
        resultPoint = convertWorldToObject(parent, point);
    } else resultPoint = point;

    return (*shape->worldToObject) * resultPoint;
}

Vector normalToWorld(Shape* &shape, Vector &normal) {
    Vector resultNormal;
    glm::mat4 transpose = glm::transpose(*shape->worldToObject);
    resultNormal = transpose * normal;
    resultNormal = glm::normalize(resultNormal);

    if (shape->parent() != nullptr) {
        Shape* parent = shape->parent();
        return normalToWorld(parent, resultNormal);
    } else 
        return resultNormal;
}

Bounds Shape::unitBounds() {
    return Bounds(createPoint(-1, -1, -1), createPoint(1, 1, 1));
}

Bounds childBounds(Shape *child) {
    Bounds unit_bounds = child->unitBounds();
    float xc = (unit_bounds.max().x + unit_bounds.min().x) / 2.0;
    float yc = (unit_bounds.max().y + unit_bounds.min().y) / 2.0;
    float zc = (unit_bounds.max().z + unit_bounds.min().z) / 2.0;

    float xd = unit_bounds.max().x - xc;
    float yd = unit_bounds.max().y - yc;
    float zd = unit_bounds.max().z - zc;

    Point center_point = createPoint(xc, yc, zc);
    Bounds child_bounds = unit_bounds;

    Point newPoint = (*child->objectToWorld) * center_point;
    child_bounds = Bounds(newPoint, newPoint);
    
    for (float x = -1; x < 2; x += 2) {
        for (float y = -1; y < 2; y += 2) {
            for (float z = -1; z < 2; z += 2) {
                Vector corner_vector = createVector(x * xd, y * yd, z * zd);
                Point corner = center_point + corner_vector;

                Point transformed_corner = (*child->objectToWorld) * corner;
                child_bounds.extendTo(transformed_corner);
            }
        }
    }

    return child_bounds;
}