#pragma once
#include <vector>
#include <map>
#include "scanline_triangulation.hpp"

namespace util::cellGen {
    typedef geometry::Vector2D Point2D;
    struct CellData {
        Point2D center;
        std::vector<Point2D> vertices;
        std::vector<CellData*> adjacent;
        CellData();
    };
    Point2D circumscribedCenter(Point2D a, Point2D b, Point2D c);
    bool isHigher(const Point2D& a, const Point2D& b, const Point2D& v);
    void convexHull(std::vector<Point2D>& vertices);
    std::vector<CellData*> getMap(Point2D canvasSize, size_t regionsCount);
    std::vector<Point2D> getRandomPoints(Point2D canvasSize, size_t pointsCount);
}