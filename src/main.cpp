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
    auto t = util::cellGen::getMap(Point2D(15360, 8640), 10000);
    auto vec = makeSurface(t);
    for (auto ob : vec) {
        engine::gameController::Instance()->registerObject(ob);
    }
    Squad* sq = new Squad(vec[0]);
    sq->action->setPath(vec[9999]);
    engine::gameController::Instance()->registerObject(sq);
    engine::gameController::Instance()->gameLoop();
    return 0;
}