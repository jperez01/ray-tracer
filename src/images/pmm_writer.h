#ifndef RTC_PMM_WRITER
#define RTC_PMM_WRITER

#include "display/canvas.h"

#include <iostream>
#include <fstream>

class PMMWriter {
    public:
        PMMWriter(Canvas* canvas);

        void writeFile(std::string name);

    private:
        Canvas* canvas_;

        int colorInt(float colorValue);
        void writeColorFloat(std::ostream &stream, float colorValue, int* line_len);
        
        void writeStream(std::ostream &stream);
        void writeHeader(std::ostream &stream);

};

#endif