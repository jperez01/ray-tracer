#include "primitives/color.h"
#include "display/canvas.h"
#include "images/pmm_writer.h"
#include "primitives/ray.h"
#include "shapes/sphere.h"
#include "primitives/color.h"
#include "lights/point_light.h"
#include "lights/direction_light.h"

#include <string>
#include <vector>
#include <thread>
#include <queue>
#include <chrono>

int size = 1000;
std::mutex queue_mutex;

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
                Tuple normal = shape->surfaceNormal(finalPosition);
                Color finalColor(0.0, 0.0, 0.0);

                for (PointLight &light : pointLights) {
                    finalColor = finalColor + calculateColorFromPoint(light, normal, finalPosition, viewDir, shape);
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
    Canvas canvas = Canvas(size, size);

    Color background(0.5, 0.5, 0.5);

    std::vector<PointLight> pointLights;
    Color pointColor(1.0, 1.0, 1.0);
    Tuple lightPosition(-20.0, 20.0, -2.0);
    pointLights.push_back(PointLight(pointColor, lightPosition));

    std::vector<DirectionalLight> dirLights;

    std::vector<Sphere> shapes;
    Color sphereColor(1.0, 0.2, 1.0);
    Material material1(sphereColor, 0.8, 0.8, 0.7, 1.0);
    Color sphereColor2(0.2, 1.0, 1.0);
    Material material2(sphereColor2);
    Tuple center = Tuple(0, 0, 10);
    Tuple center2 = Tuple(10, 10, 10);

    shapes.push_back(Sphere(center, 20, material1));
    shapes.push_back(Sphere(center2, 10, material2));

    Tuple start = Tuple(0, 0, -10.0);

    std::queue<int> rows = std::queue<int>();
    auto processor_count = std::thread::hardware_concurrency() - 3;
    std::vector<std::thread> workers;

    for (int x = 0; x < size; x++) {
        rows.push(x);
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (int i = 0; i < processor_count; ++i) {
        std::thread worker(handleRays, &rows, std::ref(canvas), std::ref(start), std::ref(background), std::ref(shapes), std::ref(pointLights), std::ref(dirLights));
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