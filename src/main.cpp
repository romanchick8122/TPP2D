#include <fstream>
#include "engine/gameController.h"
#include "util/cellgen.h"
#include "GameLogic/Cell.h"
#include "engine/GUI/Button.h"
#include "graphics/Textures.h"
#include "engine/GUI/GuiList.h"
#include "engine/GUI/GuiStrip.h"
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

    for(int i = 0; i < Player::players.size() - 1; ++i) {
        vec[200 * i + 100]->owner = Player::players[i];
        vec[200 * i + 100]->adjacent.front()->owner = Player::players[i];
        vec[200 * i + 100]->adjacent.back()->owner = Player::players[i];
    }
    //Squads::Squad* sq2 = Squads::AllTemplates[0]->build();
    //sq2->setCell(vec[9999]);
    //engine::gameController::Instance()->registerObject(sq2);
    engine::gameController::Instance()->gameLoop();
    return 0;
}