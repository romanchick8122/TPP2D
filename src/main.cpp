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

    auto* st = new engine::GUI::GuiStrip(167, engine::config::Facade::Color(60, 40, 8));
    auto* bruh1 = new engine::GUI::GuiList(engine::config::Facade::Color(255,255,255));
    bruh1->boundary.width = 76;
    bruh1->boundary.height = 42;
    st->addChild(std::unique_ptr<engine::GUI::GuiObject>(bruh1));
    auto* bruh2 = new engine::GUI::GuiList(engine::config::Facade::Color(255, 0, 0));
    bruh2->boundary.width = 76;
    bruh2->boundary.height = 42;
    st->addChild(std::unique_ptr<engine::GUI::GuiObject>(bruh2));
    auto* bruh3 = new engine::GUI::GuiList(engine::config::Facade::Color(255, 255, 255));
    bruh3->boundary.width = 76;
    bruh3->boundary.height = 42;
    st->addChild(std::unique_ptr<engine::GUI::GuiObject>(bruh3));
    st->boundary.left = 76;
    st->boundary.top = 42;
    engine::gameController::Instance()->registerStaticObject(st);

    auto* sq1 = new Squads::Squad(nullptr);
    sq1->setCell(vec[0]);
    Squads::Squad* sq2 = Squads::AllTemplates[0]->build();
    sq2->setCell(vec[9999]);
    sq1->action->setPath(vec[9999]);
    engine::gameController::Instance()->registerObject(sq1);
    engine::gameController::Instance()->registerObject(sq2);

    engine::gameController::Instance()->gameLoop();
    return 0;
}