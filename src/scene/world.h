#ifndef RTC_WORLD
#define RTC_WORLD

#include "shapes/shape.h"
#include "lights/direction_light.h"
#include "lights/point_light.h"
#include "primitives/ray.h"
#include "primitives/intersections.h"
#include "primitives/color.h"
#include "scene/computations.h"
#include <vector>

class World {
    public:
        World();
        World(std::vector<Shape *> &objects);
        World(std::vector<Shape *> &objects, std::vector<PointLight> &pointLights);
        World(std::vector<Shape *> &objects, 
            std::vector<DirectionalLight> &directLights,
            std::vector<PointLight> &pointLights);
        
        Intersections intersect(Ray &ray);
        std::optional<Intersection> intersectSimple(Ray &ray);
        Color shadeHit(Computations &computations, int remaining = 0);
        Color colorAt(Ray &ray, Color &backgroundColor, int remaining = 0);
        Color findReflection(Computations &info, int remaining = 0);
        Color findRefraction(Computations &info, int remaining = 0);
        float findReflectance(Computations &info);
        bool isShadowed(Tuple &point, PointLight &light);

        inline std::vector<Shape *> objects() { return m_objects; }
        inline std::vector<PointLight> pointLights() { return m_pointLights; }
        inline std::vector<DirectionalLight> directionalLights() { return m_directLights; }

        void setPointLights(std::vector<PointLight> newLights);

    private:
        std::vector<Shape *> m_objects;
        std::vector<PointLight> m_pointLights;
        std::vector<DirectionalLight> m_directLights;
};

World default_world();

#endif