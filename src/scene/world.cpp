#include "scene/world.h"
#include "shapes/shape.h"
#include "shapes/sphere.h"
#include "primitives/tuple.h"
#include <vector>

World::World() {
    m_objects = std::vector<Shape *>();
    m_directLights = std::vector<DirectionalLight>();
    m_pointLights = std::vector<PointLight>();
}

World::World(std::vector<Shape *> &objects) {
    m_objects = objects;
    m_directLights = std::vector<DirectionalLight>();
    m_pointLights = std::vector<PointLight>();
}

World::World(std::vector<Shape *> &objects, std::vector<PointLight> &pointLights) {
    m_objects = objects;
    m_directLights = std::vector<DirectionalLight>();
    m_pointLights = pointLights;
}

World::World(std::vector<Shape *> &objects, std::vector<DirectionalLight> &directLights, std::vector<PointLight> &pointLights) :
    m_objects(objects), m_directLights(directLights), m_pointLights(pointLights) {}

void World::setPointLights(std::vector<PointLight> newLights) {
    m_pointLights = newLights;
}

Intersections World::intersect(Ray &ray) {
    Intersections results{};
    for (Shape* &object : m_objects) {
        object->findIntersection(ray, results);
    }
    results.sortIntersections();
    return results;
}

std::optional<Intersection> World::intersectSimple(Ray &ray) {
    std::optional<Intersection> finalHit;

    for (Shape* &object: m_objects) {
        Intersections results{};
        object->findIntersection(ray, results);
        Intersection hit = results.hit();

        if ((!finalHit.has_value() || finalHit.value().m_time > hit.m_time) && hit.m_time > 0.0) {
            hit.m_shape = object;
            finalHit.emplace(hit);
        }
    }

    return finalHit;
}

Color World::shadeHit(Computations &computations) {
    Color finalColor(0.0, 0.0, 0.0);

    Tuple normal = computations.normal();
    Shape *shape = computations.object();
    Material material = shape->material();
    Tuple viewDir = computations.eye();
    Tuple finalPosition = computations.point();

    for (PointLight &light : m_pointLights) {
        finalColor = finalColor + calculateColorFromPoint(light, normal, finalPosition, viewDir, material);
    }
    for (DirectionalLight &light : m_directLights) {
        finalColor = finalColor + calculateColorFromDirection(light, normal, viewDir, shape);
    }

    return finalColor;
}

Color World::colorAt(Ray &ray, Color &backgroundColor) {
    std::optional<Intersection> finalHit = intersectSimple(ray);
    if (finalHit.has_value()) {
        Computations computations(finalHit.value(), ray);
        return shadeHit(computations);
    } else return backgroundColor;
    
}