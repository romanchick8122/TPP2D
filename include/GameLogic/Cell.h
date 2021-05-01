class Cell;

#pragma once

#include "engine/gameplayClickableGameObject.h"
#include "util/cellgen.h"
#include "AllFlags.h"
#include "engine/config.h"
#include "graphics/Facade.h"
#include "Squad.h"
#include <map>
#include "iostream"
#include "util/geometry.h"
#include "engine/actions/None.h"
#include "engine/gameController.h"
#include "engine/actions/SetSquadPath.h"
#include "AllUnits.h"
#include "AllSquadTemplates.h"

using Facade = engine::config::Facade;

std::vector<Cell *> makeSurface(std::vector<util::cellGen::CellData *> &);

namespace Comparators {
    struct Point2DComp {
        bool operator()(const util::cellGen::Point2D &, const util::cellGen::Point2D &) const;
    };
}


class Cell : public engine::gameplayClickableGameObject {
    int x = 0, y = 0, z = 0;
    std::vector<float> cellLandscapeFlags;
    std::map<const Cell *, std::vector<float>> cellBorderFlags;
    engine::config::Facade::Rect renderEdges;
    std::vector<engine::config::Facade::Point> shape;
public:
    const Facade::Point center;
    std::vector<Cell *> adjacent;
    const std::vector<float> *landscapeFlags = &cellLandscapeFlags;
    const std::map<const Cell *, std::vector<float>> *bordersFlags = &cellBorderFlags;
    const std::vector<util::cellGen::Point2D> vertices;

    Cell(const util::cellGen::CellData &);

    void setAdjacent(const util::cellGen::CellData &,
                     const std::map<util::cellGen::Point2D, Cell *, Comparators::Point2DComp> &);

    void setBorders();

    void tick() override;

    void lateTick() override;

    void render() override;

    Facade::Rect getRenderEdges() override;

    bool tryOnClick(Facade::Point pos, graphics::Event::MouseButton) override;

    void doOnClick() override;
};

