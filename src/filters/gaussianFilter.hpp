#pragma once
#include "filter.h"

namespace pbrt {

class GaussianFilter : public Filter {
public:
    GaussianFilter(const Vector2f &radius, float alpha)
        : Filter(radius), alpha(alpha), expX(std::exp(-alpha * radius.x * radius.x)),
          expY(std::exp(-alpha * radius.y * radius.y)) {}
    
    float Evaluate(const Point2f &p) const {
        return Gaussian(p.x, expX) * Gaussian(p.y, expY);
    }

private:
    const float alpha, expX, expY;

    float Gaussian(float d, float expv) const {
        return std::max(0.f, std::exp(-alpha * d * d) - expv);
    }
};

};