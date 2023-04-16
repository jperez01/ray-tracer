#pragma once
#include "filter.h"

namespace pbrt {

class LanczosSincFilter : public Filter {
public:
    LanczosSincFilter(const Vector2f &radius, float tau)
        : Filter(radius), tau(tau) { }
    float Evaluate(const Point2f &p) const{
        return WindowedSinc(p.x, radius.x) * WindowedSinc(p.y, radius.y);
    }
    float Sinc(float x) const {
        x = std::abs(x);
        if (x < 1e-5)  return 1;
        return std::sin(Pi * x) / (Pi * x);
    }
    float WindowedSinc(float x, Float radius) const {
        x = std::abs(x);
        if (x > radius) return 0;
        float lanczos = Sinc(x / tau);
        return Sinc(x) * lanczos;
    }

private:
    const float tau;
};

};