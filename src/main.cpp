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
            float convertedX = (x * deltaX) * 40.0 - 20.0;
            float convertedY = (y * deltaY) * 40.0 - 20.0;

            Tuple endPosition = Tuple(convertedX, convertedY, 0);
            Tuple rayDirection = endPosition - start;
            Ray ray(start, rayDirection);

            std::optional<Intersection> finalHit;

            for (Sphere sphere : shapes) {
                Intersections results = sphere.findIntersection(ray);
                std::optional<Intersection> hit = results.hit();

                if (hit.has_value() && !finalHit.has_value()) finalHit = hit;
                else if (hit.has_value()
                    && finalHit.value().time() > hit.value().time()) finalHit = hit;
            }

            if (finalHit.has_value()) {
                Tuple finalPosition = ray.position(finalHit.value().time());
                Shape *shape = finalHit.value().shape();
                Tuple normal = shape->surfaceNormal(finalPosition);
                Color finalColor(0.0, 0.0, 0.0);

                for (PointLight light : pointLights) {
                    finalColor = finalColor + calculateColorFromPoint(light, normal, finalPosition, shape);
                }
                for (DirectionalLight light : dirLights) {
                    finalColor = finalColor + calculateColorFromDirection(light, normal, shape);
                }
                canvas.writePixel(x, y, finalColor);
            } else {
                canvas.writePixel(x, y, background);
            }
        }
    }
}

int main() {
    Color background(0.5, 0.5, 0.5);

    std::vector<PointLight> pointLights;
    Color pointColor(0.9, 0.0, 0.9);
    Color pointColor2(0.0, 0.9, 0.0);
    Color pointColor3(0.9, 0.0, 0.0);
    Color pointColor4(0.2, 0.0, 0.5);
    Tuple lightPosition(10.0, 10.0, -5.0);
    Tuple lightPosition2(0.0, 0.0, 2.0);
    Tuple lightPosition3(10.0, 0.0, 2.0);
    Tuple lightPosition4(20, 10, -5);
    pointLights.push_back(PointLight(pointColor, lightPosition));
    pointLights.push_back(PointLight(pointColor2, lightPosition2));
    pointLights.push_back(PointLight(pointColor3, lightPosition3));
    pointLights.push_back(PointLight(pointColor4, lightPosition4));

    std::vector<DirectionalLight> dirLights;
    Color dirColor(0.0, 0.0, 0.4);
    Color dirColor2(0.0, 0.4, 0.0);
    Color dirColor3(0.0, 0.2, 0.2);
    Tuple lightDir(0.0, 0.0, 1.0);
    Tuple lightDir2(0.0, 1.0, 1.0);
    Tuple lightDir3(1.0, 1.0, 1.0);
    dirLights.push_back(DirectionalLight(lightDir.normalized(), dirColor));
    dirLights.push_back(DirectionalLight(lightDir2.normalized(), dirColor2));
    dirLights.push_back(DirectionalLight(lightDir3.normalized(), dirColor3));

    Canvas canvas = Canvas(size, size);

    std::vector<Sphere> shapes;
    Color sphereColor(0.0, 0.9, 0.9);
    Color sphereColor2(0.9, 0.9, 0.6);
    Color sphereColor3(0.0, 0.6, 0.6);
    Tuple center = Tuple(0, 0, 2);
    Tuple center2 = Tuple(10, 10, 2);
    Tuple center3 = Tuple (-10, 10, 0);
    Matrix transform1 = translationMatrix(2.0, 3.0, 1.0);
    Matrix transform2 = scaleMatrix(0.5, 2.0, 1.0);
    shapes.push_back(Sphere(center, 60, sphereColor, transform1));
    shapes.push_back(Sphere(center2, 50, sphereColor2));
    shapes.push_back(Sphere(center3, 10, sphereColor3));

    Tuple start = Tuple(0, 0, -30.0);

    std::queue<int> rows = std::queue<int>();
    const auto processor_count = std::thread::hardware_concurrency() - 1;
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