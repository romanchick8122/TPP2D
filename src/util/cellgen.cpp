#include "util/cellgen.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <set>

namespace util::cellGen {
    CellData::CellData() : center(0, 0) {}

    Point2D circumscribedCenter(Point2D a, Point2D b, Point2D c) {
        float d = 2 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
        float sa = a.x * a.x + a.y * a.y;
        float sb = b.x * b.x + b.y * b.y;
        float sc = c.x * c.x + c.y * c.y;
        float ux = (sa * (b.y - c.y) + sb * (c.y - a.y) + sc * (a.y - b.y)) / d;
        float uy = (sa * (c.x - b.x) + sb * (a.x - c.x) + sc * (b.x - a.x)) / d;
        return Point2D(ux, uy);
    }

    bool isHigher(const Point2D &a, const Point2D &b, const Point2D &v) {
        return (b.y - a.y) * (v.x - b.x) < (v.y - b.y) * (b.x - a.x);
    }

    void convexHull(std::vector<Point2D> &vertices) {
        std::sort(vertices.begin(), vertices.end(), [](auto &lhs, auto &rhs) {
            return lhs.x < rhs.x;
        });
        std::vector<Point2D> upperHull, lowerHull;
        for (int i = 0; i < vertices.size(); ++i) {
            while (upperHull.size() > 1) {
                if (isHigher(upperHull[upperHull.size() - 2], upperHull.back(), vertices[i])) {
                    upperHull.pop_back();
                } else {
                    break;
                }
            }
            upperHull.push_back(vertices[i]);
            while (lowerHull.size() > 1) {
                if (!isHigher(lowerHull[lowerHull.size() - 2], lowerHull.back(), vertices[i])) {
                    lowerHull.pop_back();
                } else {
                    break;
                }
            }
            lowerHull.push_back(vertices[i]);
        }
        vertices.clear();
        std::copy(upperHull.begin(), upperHull.end(), std::back_inserter(vertices));
        std::copy(lowerHull.rbegin() + 1, lowerHull.rend() - 1, std::back_inserter(vertices));
    }

    std::vector<CellData*> getMap(Point2D canvasSize, size_t regionsCount) {
        std::vector<Point2D> points = getRandomPoints(canvasSize, regionsCount);
        const auto builder = geometry::DelaunayBuilder::Create(std::move(points));
        geometry::DelaunayTriangulation triangulation = builder->Get();
        std::vector<CellData*> ans(triangulation.points.size());
        {
            CellData* ptr = new CellData[triangulation.points.size()];
            for (size_t i = 0; i < triangulation.points.size(); ++i) {
                ans[i] = ptr + i;
            }
        }
        for (size_t i = 0; i < triangulation.points.size(); ++i) {
            ans[i]->center = triangulation.points[i];
        }
        std::vector<Point2D> toSkipVec = triangulation.points;
        convexHull(toSkipVec);
        std::set<float> skipX;
        for (auto val : toSkipVec) {
            skipX.insert(val.x);
        }
        for (auto &edge : triangulation.graph) {
            if (skipX.find(ans[edge.first.v1]->center.x) == skipX.end() &&
                skipX.find(ans[edge.first.v2]->center.x) == skipX.end()) {
                ans[edge.first.v1]->adjacent.push_back(ans[edge.first.v2]);
                ans[edge.first.v2]->adjacent.push_back(ans[edge.first.v1]);
            }
            if (edge.first.v2 < edge.second.v1) {
                Point2D vertex = circumscribedCenter(
                        ans[edge.first.v1]->center,
                        ans[edge.first.v2]->center,
                        ans[edge.second.v1]->center
                );
                ans[edge.first.v1]->vertices.push_back(vertex);
                ans[edge.first.v2]->vertices.push_back(vertex);
                ans[edge.second.v1]->vertices.push_back(vertex);
            }
            if (edge.first.v2 < edge.second.v2) {
                Point2D vertex = circumscribedCenter(
                        ans[edge.first.v1]->center,
                        ans[edge.first.v2]->center,
                        ans[edge.second.v2]->center
                );
                ans[edge.first.v1]->vertices.push_back(vertex);
                ans[edge.first.v2]->vertices.push_back(vertex);
                ans[edge.second.v2]->vertices.push_back(vertex);
            }
        }
        auto res = std::remove_if(ans.begin(), ans.end(), [](CellData* a) {
            return a->adjacent.size() == 0;
        });
        ans.resize(res - ans.begin());
        ans.shrink_to_fit();
        for (auto &cd : ans) {
            convexHull(cd->vertices);
        }
        return ans;
    }

    std::vector<Point2D> getRandomPoints(Point2D canvasSize, size_t pointsCount) {
        std::uniform_real_distribution<> distributionX(0, canvasSize.x);
        std::uniform_real_distribution<> distributionY(0, canvasSize.y);
        std::mt19937 gen;
        gen.seed(time(nullptr));
        std::vector<Point2D> ans;
        std::uniform_real_distribution<> distribution_border(-0.5, 0.5);
        const int step = 100;
        for(int i = 0; i < canvasSize.x; i += step) ans.push_back(Point2D(i + distribution_border(gen), -step));
        for(int i = 0; i < canvasSize.x; i += step) ans.push_back(Point2D(i + distribution_border(gen), canvasSize.y + step));
        for(int i = 0; i < canvasSize.y; i += step) ans.push_back(Point2D(-step + distribution_border(gen), i));
        for(int i = 0; i < canvasSize.y; i += step) ans.push_back(Point2D(canvasSize.x + step + distribution_border(gen), i));
        ans.reserve(pointsCount);
        for (size_t i = 0; i < pointsCount; ++i) {
            ans.push_back(Point2D(distributionX(gen), distributionY(gen)));
        }
        return ans;
    }
}