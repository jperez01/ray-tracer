#include "primitives/intersection.h"

Intersection::Intersection(float time, Shape* shape) {
    m_time = time;
    m_shape = shape;
}