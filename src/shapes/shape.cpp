#include "shapes/shape.h"

Shape::Shape() :
    Shape(nullptr, nullptr, false) {
        material = Material();
    }

Shape::Shape(const Transform *objectToWorld, const Transform *worldToObject,
            bool reverseOrientation) :
    objectToWorld(objectToWorld), worldToObject(worldToObject),
    reverseOrientation(reverseOrientation) {
        if (objectToWorld != nullptr) transformSwapsHandedness = objectToWorld->SwapsHandedness();
        else transformSwapsHandedness = false;
        material = Material();
    }

Vector3f Shape::globalNormal(Point3f &position, Intersection &i) {
    Shape* shape = this;
    Point3f local_point = convertWorldToObject(shape, position);
    Vector3f local_normal = shape->surfaceNormal(local_point, i);

    return normalToWorld(shape, local_normal);
}

bool Shape::includes(Shape *other) {
    return this == other;
}

Point3f convertWorldToObject(Shape* &shape, Point3f &point) {
    Point3f resultPoint;
    if (shape->parent() != nullptr) {
        Shape *parent = shape->parent();
        resultPoint = convertWorldToObject(parent, point);
    } else resultPoint = point;

    return (*shape->worldToObject)(resultPoint);
}

Vector3f normalToWorld(Shape* &shape, Vector3f &normal) {
    Vector3f resultNormal;
    Transform transpose = Transpose(*shape->worldToObject);
    resultNormal = Normalize(transpose(normal));

    if (shape->parent() != nullptr) {
        Shape* parent = shape->parent();
        return normalToWorld(parent, resultNormal);
    } else return resultNormal;
}

Bounds Shape::unitBounds() {
    return Bounds(Point3f(-1, -1, -1), Point3f(1, 1, 1));
}

Bounds childBounds(Shape *child) {
    Bounds unit_bounds = child->unitBounds();
    float xc = (unit_bounds.max().x + unit_bounds.min().x) / 2.0;
    float yc = (unit_bounds.max().y + unit_bounds.min().y) / 2.0;
    float zc = (unit_bounds.max().z + unit_bounds.min().z) / 2.0;

    float xd = unit_bounds.max().x - xc;
    float yd = unit_bounds.max().y - yc;
    float zd = unit_bounds.max().z - zc;

    Point3f center_point(xc, yc, zc);
    Bounds child_bounds = unit_bounds;
    auto finalPoint = (*child->objectToWorld)(center_point);
    child_bounds = Bounds(finalPoint, finalPoint);
    
    for (float x = -1; x < 2; x += 2) {
        for (float y = -1; y < 2; y += 2) {
            for (float z = -1; z < 2; z += 2) {
                Vector3f corner_vector(x * xd, y * yd, z * zd);
                Point3f corner = center_point + corner_vector;

                Point3f transformed_corner = (*child->objectToWorld)(corner);
                child_bounds.extendTo(transformed_corner);
            }
        }
    }

    return child_bounds;
}