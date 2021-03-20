#include "engine/gameController.h"
#include "engine/clickableGameObject.h"
#include "util/cellgen.h"
#include "util/geometry.h"
#include "GameLogic/Cell.h"
#include "engine/config.h"
#include "Squad.h"

using util::cellGen::Point2D;
int main() {
    engine::config::Facade::Init(1920, 1080, "TPP2D", 60);
    engine::gameController controller;
    auto t = util::cellGen::getMap(Point2D(15360, 8640), 10000);
    auto vec = makeSurface(t);
    for (auto ob : vec) {
        controller.registerObject(ob);
    }
    Squad* sq = new Squad(vec[0]);
    sq->action->setPath(vec[9999]);
    controller.registerObject(sq);
    controller.gameLoop();
    return 0;
}