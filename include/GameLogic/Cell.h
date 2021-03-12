class Cell;
#pragma once
#include "engine/gameObject.h"
#include "util/cellgen.h"


class Cell : gameObject {
    util::cellGen::Point2D center;
    std::vector<util::cellGen::Point2D> vertices;
    std::vector<Cell*> adjacent;
public:
    Cell(const util::cellGen::CellData&);
    void setAdjacent(const util::cellGen::CellData&, const std::map<util::cellGen::CellData*, Cell*>&);
    void tick() override;
    void lateTick() override;
    void render(const renderParams& params) override;
    std::pair<sf::Vector2f, sf::Vector2f> getRenderEdges() override;
};
namespace justComparator{
    struct Comp{
        bool operator() (const util::cellGen::Point2D&, const util::cellGen::Point2D&) const;
    };
}
std::vector<Cell> makeSurface(std::vector<util::cellGen::CellData*>&);