#include "Cell.h"
#include <map>

Cell::Cell(const util::cellGen::CellData& cell_) : center(cell_.center), vertices(cell_.vertices) {};
void Cell::setAdjacent(const util::cellGen::CellData& cell_, const std::map<util::cellGen::CellData*, Cell*>& mp) {
    for(auto cell__ : cell_.adjacent) {
        adjacent.push_back(mp.find(cell__) -> second);
    }
}
void Cell::tick(){return;};
void Cell::lateTick(){return;};
void Cell::render(const renderParams& params){return;};
std::pair<sf::Vector2f , sf::Vector2f > Cell::getRenderEdges(){
    return {sf::Vector2f(), sf::Vector2f()};
};

bool justComparator::Comp::operator()(const util::cellGen::Point2D& t1, const util::cellGen::Point2D& t2) const {
    if(t1.x == t2.x) return t1.y  < t2.y;
    return t1.x < t2.x;
};

std::vector<Cell> makeSurface(std::vector<util::cellGen::CellData*>& cells_) {
    std::vector<Cell> cells;
    std::map<util::cellGen::Point2D, Cell*, justComparator::Comp> mp;
    for(auto cell_ : cells_){
        cells.push_back(*(new Cell(*cell_)));
        mp[cell_->center] = &cells[cells.size() - 1];
    };
}
