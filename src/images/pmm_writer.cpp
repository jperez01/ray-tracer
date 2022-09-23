#include "images/pmm_writer.h"

#include <math.h>

#include <iostream>
#include <fstream>

const int MAX_COLOR_VALUE = 255;
const int MAX_LINE_LEN = 70;

PMMWriter::PMMWriter(Canvas* canvas) {
    canvas_ = canvas;
}

void PMMWriter::writeFile(std::string filename) {
    std::ofstream stream;
    stream.open(filename);
    writeStream(stream);
    stream.close();
}

void PMMWriter::writeHeader(std::ostream &stream) {
    stream << "P3\n";
    stream << canvas_->width() << " " << canvas_->height() << "\n";
    stream << MAX_COLOR_VALUE << "\n";
}

int PMMWriter::colorInt(float color) {
    if (color >= 1.0) return 255;
    else if (color < 0.0) return 0;
    else return ceil(color * 255);
}

void PMMWriter::writeColorFloat(std::ostream &stream, float colorValue, int* line_len) {
    int color_len;
    int color = colorInt(colorValue);

    if (color >= 100) color_len = 3;
    else if (color >= 10) color_len = 2;
    else color_len = 1;

    bool space_before = *line_len != 0;
    int current_len = *line_len + color_len + (space_before ? 1 : 0);

    if (current_len >= MAX_LINE_LEN) {
        stream << "\n";
        *line_len = 0;
    } else if (space_before) {
        stream << " ";
        *line_len += 1;
    }

    *line_len += color_len;
    stream << color;
}

void PMMWriter::writeStream(std::ostream &stream) {
    writeHeader(stream);
    for (int y = 0; y < canvas_->height(); y++) {
        int line_len = 0;
        for (int x = 0; x < canvas_->width(); x++) {
            bool row_end = (x == canvas_->width() - 1);
            Color color = canvas_->pixelAt(x, y);
            writeColorFloat(stream, color.r(), &line_len);
            writeColorFloat(stream, color.g(), &line_len);
            writeColorFloat(stream, color.b(), &line_len);
            if (row_end) {
                stream << "\n";
            }
        }
    }
}