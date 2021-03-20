#include "engine/gameController.h"
#include "engine/clickableGameObject.h"
#include "util/cellgen.h"
#include "util/geometry.h"
#include "GameLogic/Cell.h"
#include "engine/config.h"
using util::cellGen::Point2D;
int main() {
    engine::config::Facade::Init(1536, 864, "TPP2D", 60);
    engine::gameController controller;
    auto t = util::cellGen::getMap(Point2D(15360, 8640), 10000);
    auto vec = makeSurface(t);
    for (auto ob : vec) {
        controller.registerObject(ob);
    }
    controller.gameLoop();
    return 0;
}