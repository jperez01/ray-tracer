#include "primitives/color.h"
#include "display/canvas.h"
#include "images/pmm_writer.h"
#include "primitives/ray.h"
#include "shapes/sphere.h"
#include "shapes/plane.h"
#include "shapes/cube.h"
#include "shapes/cylinder.h"
#include "primitives/color.h"
#include "lights/point_light.h"
#include "lights/direction_light.h"
#include "scene/camera.h"
#include "scene/world.h"
#include "patterns/striped_pattern.h"
#include "patterns/gradient_pattern.h"
#include "patterns/ring_pattern.h"

#include <string>
#include <vector>
#include <thread>
#include <queue>
#include <chrono>
#include <math.h>

int size = 1000;
std::mutex queue_mutex;

void handleRay(std::queue<int> *queue, Canvas &canvas, World &world, Camera &camera) {
    while (1) {
        int x;
        queue_mutex.lock();
        if (queue->empty()) {
            queue_mutex.unlock();
            return;
        } else {
            x = queue->front();
            queue->pop();
        }
        queue_mutex.unlock();

        Color background(0.0, 0.0, 0.0);

        for (int y = 0; y < camera.vsize(); y++) {
            Ray ray = camera.calculateRayForPixel(x, y);
            Color result = world.colorAt(ray, background, 5);

            canvas.writePixel(x, y, result);
        }
    }
}

void handleRays(std::queue<int> *queue, Canvas &canvas, Tuple &start, Color &background, 
    std::vector<Sphere> &shapes, std::vector<PointLight> &pointLights, std::vector<DirectionalLight> &dirLights) {
    while (1) {
        int x;
        queue_mutex.lock();
        if (queue->empty()) {
            queue_mutex.unlock();
            return;
        } else {
            x = queue->front();
            queue->pop();
        }
        queue_mutex.unlock();

        float deltaX = 1.0 / size;
        float deltaY = 1.0 / size;

        for (int y = 0; y < size; y++) {
            float convertedX = (x * deltaX) * 20.0 - 10.0;
            float convertedY = (y * deltaY) * 20.0 - 10.0;

            Tuple endPosition = Tuple(convertedX, convertedY, 0);
            Tuple rayDirection = endPosition - start;
            Ray ray(start, rayDirection.normalized());

            std::optional<Intersection> finalHit;

            for (Sphere &sphere : shapes) {
                Intersections results{};
                findIntersection(sphere, ray, results);
                Intersection hit = results.hit();
                if ((!finalHit.has_value() || finalHit.value().m_time > hit.m_time) && hit.m_time > 0) {
                    hit.m_shape = &sphere;
                    finalHit.emplace(hit);
                }
            }

            if (finalHit.has_value()) {
                Tuple finalPosition = ray.position(finalHit.value().m_time);
                Tuple viewDir = -ray.direction();
                auto *shape = (Sphere*) finalHit.value().m_shape;
                Material material = shape->material();
                Tuple normal = shape->surfaceNormal(finalPosition);
                Color finalColor(0.0, 0.0, 0.0);

                for (PointLight &light : pointLights) {
                    finalColor = finalColor + calculateColorFromPoint(light, normal, finalPosition, viewDir, material);
                }
                for (DirectionalLight &light : dirLights) {
                    finalColor = finalColor + calculateColorFromDirection(light, normal, viewDir, shape);
                }
                canvas.writePixel(x, y, finalColor);
            } else {
                canvas.writePixel(x, y, background);
            }
        }
    }
}

int main() {
    Canvas canvas = Canvas(500, 500);

    Tuple from = Point(0.0, 1.5, -5.0);
    Tuple to = Point(0.0, 1.0, 0.0);
    Tuple up = Vector(0.0, 1.0, 0.0);
    Matrix matrix = viewTransform(from, to, up);
    Camera camera(500.0, 500.0, M_PI/3, matrix);

    Color a(1.0, 1.0, 1.0);
    Color b(1.0, 0.2, 0.1);
    Matrix patternTransform = scaleMatrix(0.15, 1.0, 1.0);
    StripedPattern pattern(a, b, patternTransform);

    Color cr(1.0, 0.0, 0.0);
    Color cb(0.0, 0.0, 1.0);
    Matrix gradientTransform = scaleMatrix(1.0, 1.0, 1.0);
    GradientPattern gradient(cr, cb, gradientTransform);

    Color a2(0.0, 1.0, 0.0);
    Color b2(0.3, 0.0, 1.0);
    Matrix ringTransform = scaleMatrix(2.3, 1.0, 5.5);
    RingPattern ring(a2, b2, ringTransform);

    std::vector<Shape *> objects;

    Tuple point = Point(0, -5, 10);
    Tuple normal = Vector(0, 1, 0);
    Material material(Color(1.0, 0.8, 0.7), 0.4, 0.7, 0.3, 200.0, 0.5);
    Plane floor(point, normal, material);

    Matrix middle_transform = translationMatrix(-0.5, 1, 0.5);
    Material middle_material(Color(0.1, 1, 0.5), 0.1, 0.7, 0.3, 200.0, 0.5);
    middle_material.setReflective(0.4);
    middle_material.setTransparency(0.4);
    middle_material.setRefractiveIndex(DIAMOND);
    middle_material.setPattern(&pattern);
    Sphere middle_sphere(middle_material, middle_transform);

    Matrix right_sphere_transform = translationMatrix(1.5, 0.5, -0.5) * scaleMatrix(0.5, 0.5, 0.5);
    Material right_sphere_material(Color(0.5, 1, 0.1), 0.1, 0.7, 0.3, 200.0, 0.5);
    right_sphere_material.setPattern(&gradient);
    Sphere right_sphere(right_sphere_material, right_sphere_transform);

    Matrix left_sphere_transform = translationMatrix(-1.5, 0.33, -0.75) * scaleMatrix(0.33, 0.33, 0.33);
    Material left_sphere_material(Color(1, 0.8, 0.1), 0.1, 0.7, 0.3, 2.0, 0.5);
    Sphere left_sphere(left_sphere_material, left_sphere_transform);

    Matrix glassy_transform = translationMatrix(-2, 2, 5);
    Shape* glassy_thing = GlassySphere();
    glassy_thing->setTransform(glassy_transform);

    Material cube_material(Color(0.4, 0.8, 0.1), 0.2, 0.7, 0.3, 200.0, 0.5);
    Matrix cube_transform = translationMatrix(2, 2, 15) * scaleMatrix(3, 3, 1);
    Cylinder c(0.0, 10.0, cube_transform, cube_material);

    objects.push_back(&floor);
    objects.push_back(&middle_sphere);
    objects.push_back(&left_sphere);
    objects.push_back(&right_sphere);
    objects.push_back(glassy_thing);
    objects.push_back(&c);

    std::vector<PointLight> pointLights;
    Color pointColor(1.0, 1.0, 1.0);
    Tuple lightPosition(-10.0, 10.0, -10.0);
    pointLights.push_back(PointLight(pointColor, lightPosition));

    std::vector<DirectionalLight> dirLights;

    World world(objects, dirLights, pointLights);

    std::queue<int> rows = std::queue<int>();
    auto processor_count = std::thread::hardware_concurrency() - 3;
    std::vector<std::thread> workers;

    for (int x = 0; x < camera.hsize(); x++) {
        rows.push(x);
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (int i = 0; i < processor_count; ++i) {
        std::thread worker(handleRay, &rows, std::ref(canvas), std::ref(world), std::ref(camera));
        workers.emplace_back(std::move(worker));
    }

    for (auto &worker : workers) {
        worker.join();
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    std::cout << "Spent around: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;
    PMMWriter writer = PMMWriter(&canvas);
    std::string filename = "result.ppm";
    writer.writeFile(filename);

    return 0;
}