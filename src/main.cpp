#include "primitives/color.h"
#include "display/canvas.h"
#include "images/pmm_writer.h"
#include "shapes/sphere.h"
#include "scene/camera.h"
#include "scene/world.h"

#include "primitives/math.h"

#include "stb_image_write.h"

#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>
#include <math.h>
#include <iostream>
#include <fstream>

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
            Color result = world.colorAt(ray, background, 10);

            canvas.writePixel(x, y, result);
        }
    }
}

void newHandleRay(int startRow, int endRow, Canvas &canvas, World &world, Camera& camera) {
    printf("Start Index: %d End Index: %d \n", startRow, endRow);
    while (startRow < endRow) {
        Color background(0.0, 0.0, 0.0);

        for (int y = 0; y < camera.vsize(); y++) {
            Ray ray = camera.calculateRayForPixel(startRow, y);
            Color result = world.colorAt(ray, background, 15);

            canvas.writePixel(startRow, y, result);
        }
        startRow++;
    }
}

int main() {
    Canvas canvas = Canvas(500, 500);

    Point3f from = Point3f(0.0, 0.0, 1.0);
    Point3f to = Point3f(0.0, 0.0, 0.0);
    Vector3f up = Vector3f(0.0, 1.0, 0.0);
    Transform matrix = pbrt::LookAt(from, to, up);
    Camera camera(500.0, 500.0, M_PI/3, matrix);

    std::vector<Shape *> objects;

    Transform someTransform = pbrt::Translate(Vector3f(-0.5f, 1.0f, 25.0f));
    Transform someInverse = Inverse(someTransform);
    Sphere middle_sphere(&someTransform, &someInverse, false, 10.0f);
    middle_sphere.material.reflective = 0.8f;

    Transform transform2 = pbrt::Translate(Vector3f(5.0f, 0.0f, 15.0f));
    Transform inverse2 = Inverse(transform2);
    Sphere second_sphere(&transform2, &inverse2, false, 10.0f);
    middle_sphere.material.reflective = 0.8f;

    Transform transform3 = pbrt::Translate(Vector3f(-10.0f, 0.0f, 25.0f));
    Transform inverse3 = Inverse(transform3);
    Sphere third_sphere(&transform3, &inverse3, false, 20.0f);
    third_sphere.material.reflective = 0.8f;

    objects.push_back(&middle_sphere);
    objects.push_back(&second_sphere);
    objects.push_back(&third_sphere);

    std::vector<PointLight> pointLights;
    Color pointColor(0.4, 0.0, 0.0);
    Point3f lightPosition = Point3f(-30.0, 0.0, 0.0);
    pointLights.push_back(PointLight(pointColor, lightPosition));

    Color otherColor(0.0, 0.0, 0.4);
    Point3f lightPosition2 = Point3f(20.0, 0.0, 0.0);
    pointLights.push_back(PointLight(otherColor, lightPosition2));

    Color thirdColor(0.0, 0.5, 0.0);
    Point3f lightPosition3 = Point3f(0.0, 0.0, 0.0);
    pointLights.push_back(PointLight(thirdColor, lightPosition3));

    std::vector<DirectionalLight> dirLights;

    World world(objects, dirLights, pointLights);

    auto processor_count = std::thread::hardware_concurrency() - 3;
    int range = camera.hsize() / processor_count;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::vector<std::thread> workers;
    for (int i = 0; i < processor_count; ++i) {
        std::vector<int> threadRows;

        int start = i * range, end = std::min((int)camera.hsize(), (i+1) * range);

        std::thread worker(newHandleRay, start, end, std::ref(canvas), std::ref(world), std::ref(camera));
        workers.emplace_back(std::move(worker));
    }

    for (auto &worker : workers) {
        worker.join();
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    std::cout << "Spent around: " << 
        std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() 
        << "ms" << std::endl;

    int result = stbi_write_png("result.png", canvas.width(), canvas.height(), 3, canvas.convertedData(), 3 * canvas.width());
    PMMWriter writer = PMMWriter(&canvas);
    std::string filename = "result.ppm";
    writer.writeFile(filename);

    return 0;
}