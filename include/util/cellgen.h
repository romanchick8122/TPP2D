#pragma once
#include <vector>
#include <tuple>
namespace util {
    namespace cellGen {
        struct Point2D {
            float x;
            float y;
            Point2D(float rx, float ry);
        };
        struct CellData {
            Point2D center;
            std::vector<Point2D> vertices;
            std::vector<CellData*> adjacent;
        };
        std::vector<Point2D> getRandomPoints(Point2D canvasSize, size_t pointsCount);
    }
}