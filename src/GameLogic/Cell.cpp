#include "Cell.h"
#include "engine/Logger.h"

using Facade = engine::config::Facade;

bool Comparators::Point2DComp::operator()(const util::cellGen::Point2D &t1, const util::cellGen::Point2D &t2) const {
    if (t1.x == t2.x) return t1.y < t2.y;
    return t1.x < t2.x;
}

void Cell::setAdjacent(const util::cellGen::CellData &cells_,
                       const std::map<util::cellGen::Point2D, Cell *, Comparators::Point2DComp> &mp) {
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

std::vector<Cell *> makeSurface(std::vector<util::cellGen::CellData *> &cells_) {
    Flags::setFlags();
    Units::setUnits();
    Squads::setDefaultSquadTemplates();
    std::vector<Cell *> cells;
    std::map<util::cellGen::Point2D, Cell *, Comparators::Point2DComp> mp;
    for (auto cell_ : cells_) {
        cells.push_back(new Cell(*cell_));
        mp[cell_->center] = cells[cells.size() - 1];
    }
    for (int i = 0; i < cells.size(); ++i) {
        cells[i]->setAdjacent(*cells_[i], mp);
        cells[i]->setBorders();
    }
    return cells;
}

Cell::Cell(const util::cellGen::CellData &cell_) : center(cell_.center.x, cell_.center.y), vertices(cell_.vertices),
                                                   shape(cell_.vertices.size()), visible(false) {
    cellLandscapeFlags = Flags::generateLandscapeFlags();
    for (size_t i = 0; i < vertices.size(); ++i) {
        shape[i] = Facade::Point(cell_.vertices[i].x, cell_.vertices[i].y);
    }
    for (size_t i = 0; i < shape.size(); ++i) {
        production += (shape[i].y + shape[(i + 1) % shape.size()].y) / 2 * (shape[(i + 1) % shape.size()].x - shape[i].x);
    }
    production = abs(production);
    production /= 1e7;
    double minx, maxx, miny, maxy;
    minx = maxx = vertices[0].x;
    miny = maxy = vertices[0].y;
    for (auto &vert : vertices) {
        minx = std::min(minx, vert.x);
        miny = std::min(miny, vert.y);
        maxx = std::max(maxx, vert.x);
        maxy = std::max(maxy, vert.y);
    }
    renderEdges = Facade::Rect(minx, miny, maxx - minx, maxy - miny);
    engine::gameController::Instance()->networkManager.makeShared(this);
}

void Cell::tick() {
    //if(owner != Player::nullPlayer) engine::Logger::Trace(std::to_string(id) + " " + std::to_string(production) + " " + std::to_string(owner->money));
    owner->money += production;
    return;
}

void Cell::lateTick() { return; }

void Cell::render() {
    auto _owner = owner;
    if (!visible) {
        owner = Player::nullPlayer;
    }
    Facade::DrawConvexPolygon(shape, owner->color);
    Facade::DrawThickLineStrip(shape, 3, Facade::Color(255, 255, 255), true);
    owner = _owner;
};

Facade::Rect Cell::getRenderEdges() {
    return renderEdges;
};

bool Cell::tryOnClick(Facade::Point pos, graphics::Event::MouseButton) {
    if (!renderEdges.contains(pos)) {
        return false;
    }
    if (util::geometry::pointWithin(vertices, util::cellGen::Point2D(pos.x, pos.y))) {
        doOnClick();
        return true;
    }
    return false;
}

void Cell::doOnClick() {
    if (auto *squad = dynamic_cast<Squads::Squad *>(previousClick)) {
        engine::gameController::Instance()->networkManager.addAction(std::unique_ptr<engine::Action>(
                new engine::actions::SetSquadPath(squad, this)
        ));
    } else if (previousClick == this &&
        owner == Player::players[engine::gameController::Instance()->networkManager.serverId]) {
        Squads::AllTemplates[0]->build(this, owner);
        previousClick = nullptr;
    }
    previousClick = this;
}

void Cell::setOwner(Player::Player* owner_) {
    owner = owner_;
    char serverId = engine::gameController::Instance()->networkManager.serverId;
    if (owner->id != serverId) {
        for (auto& adj : adjacent) {
            adj->visible = false;
            for (auto& adjadj : adj->adjacent) {
                if (adjadj->owner->id == serverId) {
                    adj->visible = true;
                    break;
                }
            }
        }
    } else {
        visible = true;
        for (auto& adj : adjacent) {
            adj->visible = true;
        }
    }
}

void Cell::addSquad(Squads::Squad* ptr) {
    squads.insert(ptr);
}

void Cell::deleteSquad(Squads::Squad* ptr) {
    squads.erase(ptr);
}

bool Cell::isProtected() {
    return !squads.empty();
}

Squads::Squad* Cell::getSquad() {
    return *squads.begin();
}

std::string Cell::repr() {
    return "Cell (" + std::to_string(center.x) + "; " + std::to_string(center.y) + ") " + std::to_string(production);
}