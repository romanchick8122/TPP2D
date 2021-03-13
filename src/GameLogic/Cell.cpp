#include "Cell.h"
#include <map>
#include "iostream"

bool Comparators::Point2DComp::operator()(const util::cellGen::Point2D& t1, const util::cellGen::Point2D& t2) const {
    if(t1.x == t2.x) return t1.y  < t2.y;
    return t1.x < t2.x;
}
void Cell::setAdjacent(const util::cellGen::CellData& cells_, const std::map<util::cellGen::Point2D, Cell*, Comparators::Point2DComp>& mp){
    for(auto cell__ : cells_.adjacent) {
        adjacent.push_back(mp.find(cell__ -> center) -> second);
    }
}

void Cell::setBorders() {
    for(auto cellPtr : adjacent) {
        int xx = adjacent.size();
        std::map<Cell*, std::vector<float>>* ptr = &cellBorderFlags;
        cellBorderFlags[cellPtr] = std::vector<float>(1, 133);
        //std::vector<float> b = Flags::generateBorderFlags();
    }
}

std::vector<Cell*> makeSurface(std::vector<util::cellGen::CellData*>& cells_) {
    Flags::setFlags();
    std::vector<Cell*> cells;
    std::map<util::cellGen::Point2D, Cell*, Comparators::Point2DComp> mp;
    for(auto cell_ : cells_) {
        cells.push_back(new Cell(*cell_));
        //std::map<Cell*, std::vector<float>>* ptr = &cl.cellBorderFlags;
        std::map<Cell*, std::vector<float>>* ptr2 = &cells[0]->cellBorderFlags;
        mp[cell_->center] = cells[cells.size() - 1];
    };
    for(int i = 0; i < cells.size(); ++i) {
        cells[i]->setAdjacent(*cells_[i], mp);
        cells[i]->setBorders();
        std::cout << "0";
    }
    return cells;
}

Cell::Cell(const util::cellGen::CellData& cell_) : center(cell_.center), vertices(cell_.vertices) {
    std::map<Cell*, std::vector<float>>* ptr = &cellBorderFlags;
    cellLandscapeFlags = Flags::generateLandscapeFlags();
};
void Cell::tick(){return;};
void Cell::lateTick(){return;};
void Cell::render(const engine::renderParams& params){return;};
sf::FloatRect Cell::getRenderEdges(){
    return {sf::Vector2f(), sf::Vector2f()};
};



