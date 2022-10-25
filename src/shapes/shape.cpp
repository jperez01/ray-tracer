#include "shapes/shape.h"

Tuple Shape::globalNormal(Tuple &position, Intersection &i) {
    Shape* shape = this;
    Tuple local_point = worldToObject(shape, position);
    Tuple local_normal = shape->surfaceNormal(local_point, i);

    return normalToWorld(shape, local_normal);
}

bool Shape::includes(Shape *other) {
    return this == other;
}

Tuple worldToObject(Shape* &shape, Tuple &point) {
    Tuple resultPoint;
    if (shape->parent() != nullptr) {
        Shape *parent = shape->parent();
        resultPoint = worldToObject(parent, point);
    } else resultPoint = point;

    if (shape->transform().has_value()) {
        return shape->transform().value().inverse() * resultPoint;
    } else return resultPoint;
}

Tuple normalToWorld(Shape* &shape, Tuple &normal) {
    Tuple resultNormal;
    if (shape->transform().has_value()) {
        Matrix transpose = shape->transform().value().inverse().transpose();
        resultNormal = transpose * normal;
        resultNormal.w = 0;
        resultNormal = resultNormal.normalized();
    } else resultNormal = normal;

    if (shape->parent() != nullptr) {
        Shape* parent = shape->parent();
        return normalToWorld(parent, resultNormal);
    } else return resultNormal;
}

Bounds Shape::unitBounds() {
    return Bounds(Point(-1, -1, -1), Point(1, 1, 1));
}

Bounds childBounds(Shape *child) {
    Bounds unit_bounds = child->unitBounds();
    float xc = (unit_bounds.max().x + unit_bounds.min().x) / 2.0;
    float yc = (unit_bounds.max().y + unit_bounds.min().y) / 2.0;
    float zc = (unit_bounds.max().z + unit_bounds.min().z) / 2.0;

    float xd = unit_bounds.max().x - xc;
    float yd = unit_bounds.max().y - yc;
    float zd = unit_bounds.max().z - zc;

    Tuple center_point = Point(xc, yc, zc);
    Bounds child_bounds = unit_bounds;
    if (child->transform().has_value()) {
        child_bounds = Bounds(child->transform().value() * center_point, child->transform().value() * center_point);
    } else {
        child_bounds = Bounds(center_point, center_point);
    }
    
    for (float x = -1; x < 2; x += 2) {
        for (float y = -1; y < 2; y += 2) {
            for (float z = -1; z < 2; z += 2) {
                Tuple corner_vector = Vector(x * xd, y * yd, z * zd);
                Tuple corner = center_point + corner_vector;
                if (child->transform().has_value()) {
                    Tuple transformed_corner = child->transform().value() * corner;
                    child_bounds.extendTo(transformed_corner);
                } else {
                    child_bounds.extendTo(corner);
                }
            }
        }
    }

    return child_bounds;
}