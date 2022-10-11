#include "scene/world.h"
#include "shapes/shape.h"
#include "shapes/sphere.h"
#include "primitives/tuple.h"
#include <vector>
#include <cmath>

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

Color World::shadeHit(Computations &computations, int remaining) {
    Color finalColor(0.0, 0.0, 0.0);

    Tuple normal = computations.normal();
    Shape *shape = computations.object();
    Tuple viewDir = computations.eye();
    Tuple finalPosition = computations.point();
    Tuple overPoint = computations.overPoint();

    Color reflected_color = findReflection(computations, remaining);
    Color refracted_color = findRefraction(computations, remaining);


    for (PointLight &light : m_pointLights) {
        bool inShadow = isShadowed(overPoint, light);
        finalColor = finalColor + calculateColorFromPoint(light, normal, overPoint, viewDir, *shape, inShadow);
    }
    
    for (DirectionalLight &light : m_directLights) {
        finalColor = finalColor + calculateColorFromDirection(light, normal, viewDir, shape);
    }

    Material material = shape->material();
    if (material.reflective() > 0 && material.transparency() > 0) {
        float reflectance = findReflectance(computations);
        return finalColor + reflected_color * reflectance
            + refracted_color * (1 - reflectance);
    }

    return finalColor + reflected_color + refracted_color;
}

Color World::colorAt(Ray &ray, Color &backgroundColor, int remaining) {
    std::optional<Intersection> finalHit = intersectSimple(ray);
    if (finalHit.has_value()) {
        Computations computations(finalHit.value(), ray);
        return shadeHit(computations, remaining);
    } else return backgroundColor;
}

Color World::findReflection(Computations &info, int remaining) {
    Color defaultColor(0, 0, 0);
    if (remaining < 1 || info.object()->material().reflective() == 0.0)
        return defaultColor;

    Ray reflect_ray(info.overPoint(), info.reflectv());
    Color result = colorAt(reflect_ray, defaultColor, remaining - 1);

    return result * info.object()->material().reflective();
}

Color World::findRefraction(Computations &info, int remaining) {
    Color defaultColor(0.0, 0.0, 0.0);
    if (remaining < 1 || info.object()->material().transparency() == 0.0) return defaultColor;

    float n_ratio = info.refract1() / info.refract2();

    float cos_i = dot(info.eye(), info.normal());
    float sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);
    if (sin2_t > 1.0) return defaultColor;

    float cos_t = sqrt(1.0 - sin2_t);

    Tuple direction = info.normal() * (n_ratio * cos_i - cos_t)
        - info.eye() * n_ratio;
    
    Ray refract_ray(info.underPoint(), direction);

    float transparency = info.object()->material().transparency();
    Color result = transparency * colorAt(refract_ray, defaultColor, remaining - 1);

    return result;
}

float World::findReflectance(Computations &info) {
    float cos = dot(info.eye(), info.normal());

    if (info.refract1() > info.refract2()) {
        float n = info.refract1() / info.refract2();
        float sin2_t = n * n * (1.0 - cos * cos);
        if (sin2_t > 1.0) return 1.0;

        float cos_t = sqrt(1.0 - sin2_t);
        cos = cos_t;
    }

    float value = (info.refract1() - info.refract2()) / (info.refract1() + info.refract2());
    float r0 = powf(value, 2);
    return (1 - r0) * powf((1.0 - cos), 5) + r0;
}

bool World::isShadowed(Tuple &point, PointLight &light) {
    Tuple direction = light.position() - point;
    float distance = direction.magnitude();
    direction = direction.normalized();

    Ray ray(point, direction);
    std::optional<Intersection> finalHit = intersectSimple(ray);

    return finalHit.has_value() && finalHit.value().m_time < distance;
}