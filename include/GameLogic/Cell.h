class Cell;
#pragma once
#include "engine/gameObject.h"
#include "util/cellgen.h"
#include "AllFlags.h"
#include "engine/config.h"
#include "graphics/Facade.h"
using Facade = engine::config::Facade;
std::vector<Cell*> makeSurface(std::vector<util::cellGen::CellData*>&);
namespace Comparators {
    struct Point2DComp {
        bool operator() (const util::cellGen::Point2D&, const util::cellGen::Point2D&) const;
    };
}


class Cell : public engine::gameObject {
    int x = 0,y = 255,z = 255;
    std::vector<float> cellLandscapeFlags;
    std::map<const Cell*, std::vector<float>> cellBorderFlags;
    engine::config::Facade::Rect renderEdges;
    std::vector<engine::config::Facade::Point> shape;
public:
    const Facade::Point center;
    std::vector<Cell*> adjacent;
    const std::vector<float>* landscapeFlags = &cellLandscapeFlags;
    const std::map<const Cell*, std::vector<float>>* bordersFlags = &cellBorderFlags;
    const std::vector<util::cellGen::Point2D> vertices;

    Cell(const util::cellGen::CellData&);
    void setAdjacent(const util::cellGen::CellData&, const std::map<util::cellGen::Point2D , Cell*, Comparators::Point2DComp>&);
    void setBorders();
    //todo две функции на похуй меняют приватные поля, звучит хуево

    void tick() override;
    void lateTick() override;
    void render() override;
    Facade::Rect getRenderEdges() override;
    bool tryOnClick(Facade::Point pos, graphics::Event::MouseButton) override;
};

