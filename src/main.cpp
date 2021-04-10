#include <fstream>
#include "engine/gameController.h"
#include "util/cellgen.h"
#include "GameLogic/Cell.h"
#include "Squad.h"
#include "engine/GUI/Button.h"
#include "graphics/Textures.h"
#ifdef WIN32
#include "winsock2.h"
#endif
using util::cellGen::Point2D;
std::string readFile(std::string filename) {
    std::ifstream t(filename);
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
               std::istreambuf_iterator<char>());
    return str;
}
int main() {
    //init sockets
#ifdef WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    engine::config::runtime = nlohmann::json::parse(readFile("config.json"), nullptr, false, true);
    graphics::Textures::loadTextures();

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