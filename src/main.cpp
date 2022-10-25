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

#include "extras/obj_parser.h"

#include <string>
#include <vector>
#include <thread>
#include <queue>
#include <chrono>
#include <math.h>
#include <iostream>
#include <fstream>

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

int main() {
    Canvas canvas = Canvas(500, 500);

    Tuple from = Point(-6.0, 6.0, -10.0);
    Tuple to = Point(6.0, 0, 6.0);
    Tuple up = Vector(-0.45, 1.0, 0.0);
    Matrix matrix = viewTransform(from, to, up);
    Camera camera(500.0, 500.0, 0.785, matrix);

    Color whiteColor(1.0, 1.0, 1.0);
    Material whiteMaterial(whiteColor, 0.1, 0.0, 0.7, 1.0);
    whiteMaterial.setReflective(0.1);

    Color blueColor(0.537, 0.831, 0.914);
    Material blueMaterial(blueColor, 0.1, 0.0, 0.7, 0.1);

    Color redColor(0.941, 0.322, 0.388);
    Material redMaterial(redColor, 0.1, 0.0, 0.7, 0.1);

    Color purpleColor(0.373, 0.404, 0.550);
    Material purpleMaterial(blueColor, 0.1, 0.0, 0.7, 0.1);

    Matrix standardTransform = translationMatrix(1, -1, 1) * scaleMatrix(0.5, 0.5, 0.5);
    Matrix largeObject = scaleMatrix(3.5, 3.5, 3.5) * standardTransform;
    Matrix mediumObject = scaleMatrix(3, 3, 3) * standardTransform;
    Matrix smallObject = scaleMatrix(2, 2, 2) * standardTransform;

    Tuple planePoint(0, 0.0, 0);
    Tuple planeNormal(0, 0.0, 1.0);
    Matrix planeTransform = translationMatrix(0, 0, 500);
    Color planeColor(1.0, 1.0, 0.0);
    Material planeMaterial(planeColor, 1.0, 0.0, 0.0, 1.0);
    Plane plane(planePoint, planeNormal, planeTransform, planeMaterial);

    Material sphereMaterial(purpleColor, 0.0, 1.0, 0.2, 200);
    sphereMaterial.setReflective(0.7);
    sphereMaterial.setTransparency(0.7);
    sphereMaterial.setRefractiveIndex(1.5);
    Sphere sphere(sphereMaterial, largeObject);

    Matrix cube1Transform = translationMatrix(4, 0, 0) * mediumObject;
    Cube cube(cube1Transform, whiteMaterial);

    Matrix cube2Transform = translationMatrix(8.5, 1.5, -0.5) * largeObject;
    Cube cube2(cube2Transform, blueMaterial);

    Matrix cube3Transform = translationMatrix(0, 0, 4) * largeObject;
    Cube cube3(cube3Transform, redMaterial);

    Matrix cube4Transform = translationMatrix(4, 0, 4) * smallObject;
    Cube cube4(cube4Transform, whiteMaterial);

    Matrix cube5Transform = translationMatrix(7.5, 0.5, 4) * mediumObject;
    Cube cube5(cube5Transform, purpleMaterial);

    Matrix cube6Transform = translationMatrix(-0.25, 0.25, 8) * mediumObject;
    Cube cube6(cube6Transform, whiteMaterial);

    Matrix cube7Transform = translationMatrix(4, 1, 7.5) * largeObject;
    Cube cube7(cube7Transform, blueMaterial);

    Matrix cube8Transform = translationMatrix(10, 2, 7.5) * mediumObject;
    Cube cube8(cube8Transform, redMaterial);

    Matrix cube9Transform = translationMatrix(8, 2, 12) * smallObject;
    Cube cube9(cube9Transform, whiteMaterial);

    Matrix cube10Transform = translationMatrix(20, 1, 9) * smallObject;
    Cube cube10(cube10Transform, whiteMaterial);

    Matrix cube11Transform = translationMatrix(-0.5, -5, 0.25) * largeObject;
    Cube cube11(cube11Transform, blueMaterial);

    Matrix cube12Transform = translationMatrix(4, -4, 0) * largeObject;
    Cube cube12(cube12Transform, redMaterial);

    Matrix cube13Transform = translationMatrix(8.5, -4, 0) * largeObject;
    Cube cube13(cube13Transform, whiteMaterial);

    Matrix cube14Transform = translationMatrix(0, -4, 4) * largeObject;
    Cube cube14(cube14Transform, whiteMaterial);

    Matrix cube15Transform = translationMatrix(-0.5, -4.5, 8) * largeObject;
    Cube cube15(cube15Transform, purpleMaterial);

    Matrix cube16Transform = translationMatrix(0, -8, 4) * largeObject;
    Cube cube16(cube16Transform, whiteMaterial);

    Matrix cube17Transform = translationMatrix(-0.5, -8.5, 8) * largeObject;
    Cube cube17(cube17Transform, whiteMaterial);

    std::vector<Shape *> objects;

    objects.push_back(&sphere);
    objects.push_back(&cube);
    objects.push_back(&cube2);
    objects.push_back(&cube3);
    objects.push_back(&cube4);
    objects.push_back(&cube5);
    objects.push_back(&cube6);
    objects.push_back(&cube7);
    objects.push_back(&cube8);
    objects.push_back(&cube9);
    objects.push_back(&cube10);
    objects.push_back(&cube11);
    objects.push_back(&cube12);
    objects.push_back(&cube13);
    objects.push_back(&cube14);
    objects.push_back(&cube15);
    objects.push_back(&cube16);
    objects.push_back(&cube17);


    std::vector<PointLight> pointLights;
    Color pointColor(1.0, 1.0, 1.0);
    Tuple lightPosition = Point(50.0, 100.0, -50.0);
    pointLights.push_back(PointLight(pointColor, lightPosition));

    Color otherColor(0.2, 0.2, 0.2);
    Tuple lightPosition2 = Point(-400.0, 50.0, -10.0);
    pointLights.push_back(PointLight(otherColor, lightPosition2));

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