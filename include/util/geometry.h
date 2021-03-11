#pragma once
#include <vector>
#include "util/cellgen.h"
namespace util::geometry {
    template<typename T, typename U>
    float pointsAngle(T a, U b);
    bool pointWithin(std::vector<util::cellGen::Point2D> polygon, util::cellGen::Point2D point);
    template<typename T>
    float semiplaneSide(T a, T b, T c);
}