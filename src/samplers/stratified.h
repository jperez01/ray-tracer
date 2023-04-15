#pragma once

#include "sampler.h"
#include "sampling.h"

namespace pbrt {

class StratifiedSampler : public PixelSampler {
public:
    StratifiedSampler(int xPixelSamples, int yPixelSamples, bool jitterSamples,
                      int nSampledDimensions)
        : PixelSampler(xPixelSamples * yPixelSamples, nSampledDimensions),
          xPixelSamples(xPixelSamples),
          yPixelSamples(yPixelSamples),
          jitterSamples(jitterSamples) {}

    void StartPixel(const Point2i &p);
    std::unique_ptr<Sampler> Clone(int seed);

    Float Get1D();
    Point2f Get2D();

private:
    const int xPixelSamples, yPixelSamples;
    const bool jitterSamples;
};

};