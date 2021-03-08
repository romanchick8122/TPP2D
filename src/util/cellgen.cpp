#include "util/cellgen.h"
#include <random>
namespace util {
    namespace cellGen {
        Point2D::Point2D(float rx, float ry) : x(rx), y(ry) { }
        std::vector<Point2D> getRandomPoints(Point2D canvasSize, size_t pointsCount) {
            std::uniform_real_distribution<> distributionX(0, canvasSize.x);
            std::uniform_real_distribution<> distributionY(0, canvasSize.y);
            std::mt19937 gen;
            std::vector<Point2D> ans;
            ans.reserve(pointsCount);
            for (size_t i = 0; i < pointsCount; ++i) {
                ans.push_back(Point2D(distributionX(gen), distributionY(gen)));
            }
            return ans;
        }
    }
}