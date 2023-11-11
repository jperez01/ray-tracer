#pragma once

#include "core/filter.h"

namespace pbrt {

    class GaussianFilter : public Filter {
    public:
        GaussianFilter(const Vector2f& radius, float alpha)
            : Filter(radius), alpha(alpha), expX(std::exp(-alpha * radius.x * radius.x)),
            expY(std::exp(-alpha * radius.y * radius.y)) {}

        float Evaluate(const Point2f& p) const {
            return Gaussian(p.x, expX) * Gaussian(p.y, expY);
        }

    private:
        const float alpha, expX, expY;

        float Gaussian(float d, float expv) const {
            return std::max(0.f, std::exp(-alpha * d * d) - expv);
        }
    };

    class BoxFilter : public Filter {
    public:
        BoxFilter(const Vector2f& radius) : Filter(radius) {}
        float Evaluate(const Point2f& p) const {
            return 1.f;
        }
    };

    class LanczosSincFilter : public Filter {
    public:
        LanczosSincFilter(const Vector2f& radius, float tau)
            : Filter(radius), tau(tau) { }
        float Evaluate(const Point2f& p) const {
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

    class MitchellFilter : public Filter {
    public:
        MitchellFilter(const Vector2f& radius, Float B, Float C)
            : Filter(radius), B(B), C(C) {
        }
        Float Evaluate(const Point2f& p) const {
            return Mitchell1D(p.x * invRadius.x) * Mitchell1D(p.y * invRadius.y);
        }
        Float Mitchell1D(Float x) const {
            x = std::abs(2 * x);
            if (x > 1)
                return ((-B - 6 * C) * x * x * x + (6 * B + 30 * C) * x * x +
                    (-12 * B - 48 * C) * x + (8 * B + 24 * C)) * (1.f / 6.f);
            else
                return ((12 - 9 * B - 6 * C) * x * x * x +
                    (-18 + 12 * B + 6 * C) * x * x +
                    (6 - 2 * B)) * (1.f / 6.f);
        }

    private:
        const float B, C;
    };

    class TriangleFilter : public Filter {
    public:
        TriangleFilter(const Vector2f& radius) : Filter(radius) {}
        float Evaluate(const Point2f& p) const {
            return std::max(0.f, radius.x - std::abs(p.x)) *
                std::max(0.f, radius.y - std::abs(p.y));
        }
    };


};