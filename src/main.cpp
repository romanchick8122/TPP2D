#include "engine/gameController.h"
#include "engine/clickableGameObject.h"
#include "util/cellgen.h"
#include "util/geometry.h"
#include "GameLogic/Cell.h"
#include "engine/config.h"

using util::cellGen::Point2D;
int main() {
    engine::config::Facade::Init(1920, 1080, "TPP2D", 60);
    auto t = util::cellGen::getMap(Point2D(15360, 8640), 10000);
    auto vec = makeSurface(t);
    for (auto ob : vec) {
        engine::gameController::Instance()->registerObject(ob);
    }
    engine::gameController::Instance()->gameLoop();
    return 0;
}