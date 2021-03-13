class Cell;
#pragma once
#include "engine/gameObject.h"
#include "util/cellgen.h"
#include "AllFlags.h"

std::vector<Cell*> makeSurface(std::vector<util::cellGen::CellData*>&);
namespace Comparators {
    struct Point2DComp {
        bool operator() (const util::cellGen::Point2D&, const util::cellGen::Point2D&) const;
    };
}


class Cell : engine::gameObject {
    util::cellGen::Point2D center;
    std::vector<float> cellLandscapeFlags;
public:
    std::map<Cell*, std::vector<float>> cellBorderFlags;
    std::vector<Cell*> adjacent;
    const std::vector<float>* landscapeFlags = &cellLandscapeFlags;
    const std::map<Cell*, std::vector<float>>* bordersFlags = &cellBorderFlags;
    const std::vector<util::cellGen::Point2D> vertices;

    Cell(const util::cellGen::CellData&);
    void setAdjacent(const util::cellGen::CellData&, const std::map<util::cellGen::Point2D , Cell*, Comparators::Point2DComp>&);
    void setBorders();
    //todo две функции на похуй меняют приватные поля, звучит хуево

    void tick() override;
    void lateTick() override;
    void render(const engine::renderParams& params) override;
    sf::FloatRect getRenderEdges() override;

};

