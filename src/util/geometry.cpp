#include "util/geometry.h"
#include <algorithm>
#include <cmath>
using util::cellGen::Point2D;
namespace util::geometry {
    template<typename T, typename U>
    float pointsAngle(T a, U b) {
        return atan2f(b.x - a.x, b.y - a.y);
    }
    bool pointWithin(std::vector<Point2D> polygon, Point2D point) {
        bool ok = (semiplaneSide(polygon[0], polygon[1], point) > 0);
        for (int i = 0; i < polygon.size(); ++i) {
            if (ok != (semiplaneSide(polygon[i], polygon[(i + 1) % polygon.size()], point) > 0)) {
                return false;
            }
        }
        return true;
    }
    template<typename T>
    float semiplaneSide(T a, T b, T c) {
        return (a.x - c.x) * (b.y - c.y) - (b.x - c.x) * (a.y - c.y);
    }
}