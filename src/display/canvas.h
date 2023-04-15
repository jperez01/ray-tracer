#ifndef RTC_CANVAS
#define RTC_CANVAS

#include "primitives/color.h"

class Canvas {
    public:
        Canvas(int h, int w);

        void writePixel(int x, int y, Color color);

        Color pixelAt(int x, int y);
        int pixelIndex(int x, int y);

        int width() { return width_; }
        int height() { return height_; }

        float* data() { return this->data_; }
        char* convertedData() { return this->converted_data; }

    private:
        int width_;
        int height_;
        float *data_;

        char *converted_data;
};

#endif