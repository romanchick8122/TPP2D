#include "Cell.h"
#include <map>
#include "iostream"
#include "util/geometry.h"
#include "engine/config.h"
#include "engine/actions/None.h"
using Facade = engine::config::Facade;
bool Comparators::Point2DComp::operator()(const util::cellGen::Point2D& t1, const util::cellGen::Point2D& t2) const {
    if (t1.x == t2.x) return t1.y < t2.y;
    return t1.x < t2.x;
}
void Cell::setAdjacent(const util::cellGen::CellData& cells_,
                       const std::map<util::cellGen::Point2D, Cell*, Comparators::Point2DComp>& mp) {
    for (auto cell__ : cells_.adjacent) {
        adjacent.push_back(mp.find(cell__->center)->second);
    }
}

void Cell::setBorders() {
    for (auto cellPtr : adjacent) {
        int xx = adjacent.size();
        cellBorderFlags[cellPtr] = std::vector<float>(1, 133);
    }
}

std::vector<Cell*> makeSurface(std::vector<util::cellGen::CellData*>& cells_) {
    Flags::setFlags();
    std::vector<Cell*> cells;
    std::map<util::cellGen::Point2D, Cell*, Comparators::Point2DComp> mp;
    for (auto cell_ : cells_) {
        cells.push_back(new Cell(*cell_));
        mp[cell_->center] = cells[cells.size() - 1];
    };
    for (int i = 0; i < cells.size(); ++i) {
        cells[i]->setAdjacent(*cells_[i], mp);
        cells[i]->setBorders();
    }
    return cells;
}


Cell::Cell(const util::cellGen::CellData& cell_) : center(cell_.center.x, cell_.center.y), vertices(cell_.vertices),
shape(cell_.vertices.size()) {
    cellLandscapeFlags = Flags::generateLandscapeFlags();
    for (size_t i = 0; i < vertices.size(); ++i) {
        shape[i] = Facade::Point(cell_.vertices[i].x, cell_.vertices[i].y);
    }
    double minx, maxx, miny, maxy;
    minx = maxx = vertices[0].x;
    miny = maxy = vertices[0].y;
    for (auto& vert : vertices) {
        minx = std::min(minx, vert.x);
        miny = std::min(miny, vert.y);
        maxx = std::max(maxx, vert.x);
        maxy = std::max(maxy, vert.y);
    }
    renderEdges = Facade::Rect(minx, miny, maxx - minx, maxy - miny);
};
void Cell::tick() { return; };
void Cell::lateTick() { return; };
void Cell::render() {
    Facade::DrawConvexPolygon(shape, Facade::Color(0, 0, 0));
    Facade::DrawThickLineStrip(shape, 3, Facade::Color(255, 255, 255), true);
};
Facade::Rect Cell::getRenderEdges() {
    return renderEdges;
};
std::unique_ptr<engine::Action> Cell::tryOnClick(Facade::Point pos, graphics::Event::MouseButton) {
    if (util::geometry::pointWithin(vertices, util::cellGen::Point2D(pos.x, pos.y))) {
        x = 0;
        y = 0;
        z = 255;
        return std::unique_ptr<engine::Action>(new engine::actions::None());
    }
    return std::unique_ptr<engine::Action>(nullptr);
}
Facade::Rect Cell::getClickEdges() {
    return renderEdges;
}


