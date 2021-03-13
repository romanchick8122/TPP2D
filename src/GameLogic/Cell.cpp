#include "Cell.h"
#include <map>
#include "iostream"
#include "util/geometry.h"

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
        std::map<const Cell*, std::vector<float>>* ptr = &cellBorderFlags;
        cellBorderFlags[cellPtr] = std::vector<float>(1, 133);
        //std::vector<float> b = Flags::generateBorderFlags();
    }
}

std::vector<Cell*> makeSurface(std::vector<util::cellGen::CellData*>& cells_) {
    Flags::setFlags();
    std::vector<Cell*> cells;
    std::map<util::cellGen::Point2D, Cell*, Comparators::Point2DComp> mp;
    for (auto cell_ : cells_) {
        cells.push_back(new Cell(*cell_));
        //std::map<Cell*, std::vector<float>>* ptr = &cl.cellBorderFlags;
        std::map<const Cell*, std::vector<float>>* ptr2 = &cells[0]->cellBorderFlags;
        mp[cell_->center] = cells[cells.size() - 1];
    };
    for (int i = 0; i < cells.size(); ++i) {
        cells[i]->setAdjacent(*cells_[i], mp);
        cells[i]->setBorders();
    }
    return cells;
}


Cell::Cell(const util::cellGen::CellData& cell_) : center(cell_.center), vertices(cell_.vertices),
shape(cell_.vertices.size()) {
    std::map<const Cell*, std::vector<float>>* ptr = &cellBorderFlags;
    cellLandscapeFlags = Flags::generateLandscapeFlags();
    double minx, maxx, miny, maxy;
    minx = maxx = vertices[0].x;
    miny = maxy = vertices[0].y;
    for (auto& vert : vertices) {
        minx = std::min(minx, vert.x);
        miny = std::min(miny, vert.y);
        maxx = std::max(maxx, vert.x);
        maxy = std::max(maxy, vert.y);
    }
    renderEdges = sf::FloatRect(minx, miny, maxx - minx, maxy - miny);
    for (int i = 0; i < vertices.size(); ++i) {
        shape.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
    }
    shape.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
};
void Cell::tick() { return; };
void Cell::lateTick() { return; };
void Cell::render(const engine::renderParams& params) {
    shape.setOrigin(params.origin);
    shape.setScale(params.scale, params.scale);
    shape.setOutlineColor(sf::Color(127, 127, 127));
    params.targetWindow->draw(shape);
};
sf::FloatRect Cell::getRenderEdges() {
    return renderEdges;
};
bool Cell::tryOnClick(sf::Vector2f pos) {
    if (util::geometry::pointWithin(vertices, util::cellGen::Point2D(pos.x, pos.y))) {
        return true;
    }
    return false;
}
sf::FloatRect Cell::getClickEdges() {
    return renderEdges;
}


