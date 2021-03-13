#include "engine/gameController.h"
#include "engine/clickableGameObject.h"
#include "util/cellgen.h"
#include "util/geometry.h"
#include "GameLogic/Cell.h"
using util::cellGen::Point2D;
int main() {
    engine::gameController controller(1536, 864, "TPP2D", 60);
    auto t = util::cellGen::getMap(Point2D(15360, 8640), 10000);
    auto vec = makeSurface(t);
    for (auto ob : vec) {
        controller.registerObject(ob);
    }
    controller.gameLoop();
    return 0;
}