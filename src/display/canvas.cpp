#include "display/canvas.h"

#include <cassert>
#include <cstdlib>
#include <mutex>

std::mutex mutex_;

Canvas::Canvas(int h, int w) {
    height_ = h;
    width_ = w;
    data_ = (float *)calloc(sizeof(float), height_ * width_ * 3);
    converted_data = (char*) calloc(sizeof(char), height_ * width_ * 3);
}

int Canvas::pixelIndex(int x, int y) {
    assert(x >= 0);
    assert(x < width());
    assert(y >= 0);
    assert(y < height());

    return 3 * (x + y * width());
}

Color Canvas::pixelAt(int x, int y) {
    std::lock_guard<std::mutex> guard(mutex_);
    int index = pixelIndex(x, y);

    float r = data_[index++];
    float g = data_[index++];
    float b = data_[index++];

    return Color(r, g, b);
}

void Canvas::writePixel(int x, int y, Color color) {
    std::lock_guard<std::mutex> guard(mutex_);
    int index = pixelIndex(x, y);
    int convertedIndex = index;

    data_[index++] = color.r();
    data_[index++] = color.g();
    data_[index++] = color.b();

    converted_data[convertedIndex++] = color.r() * 255;
    converted_data[convertedIndex++] = color.g() * 255;
    converted_data[convertedIndex++] = color.b() * 255;
}