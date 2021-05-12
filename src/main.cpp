#include <fstream>
#include "engine/gameController.h"
#include "util/cellgen.h"
#include "GameLogic/Cell.h"
#include "engine/GUI/Button.h"
#include "graphics/Textures.h"
#include "engine/GUI/GuiList.h"
#include "engine/GUI/GuiStrip.h"
#include "Player.h"
#include "engine/Logger.h"
#include "AllUnits.h"
#ifdef WIN32
#include "winsock2.h"
#else
#include "sys/socket.h"
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
class MoneyShower : public engine::gameObject {
    std::unique_ptr<engine::GUI::Button> moneyButton;
    Player::Player* owner;
  public:
    MoneyShower(Player::Player* _owner) : owner(_owner), moneyButton(new engine::GUI::Button(
        engine::config::Facade::Rect({1920 - 100, 0}, {100, 42}),
        [](engine::GUI::Button*) {},
        engine::config::Facade::Color(0, 0, 0),
        "",
        engine::config::Facade::Color(255, 215, 0)
    )) {}
    void tick() override {
        if (owner->money > 1e16) {
            moneyButton->Text = std::to_string(static_cast<int>(owner->money / 1e15)) + "P";
        } else if (owner->money > 1e13) {
            moneyButton->Text = std::to_string(static_cast<int>(owner->money / 1e12)) + "T";
        } else if (owner->money > 1e10) {
            moneyButton->Text = std::to_string(static_cast<int>(owner->money / 1e9)) + "G";
        } else if (owner->money > 1e7) {
            moneyButton->Text = std::to_string(static_cast<int>(owner->money / 1e6)) + "M";
        } else if (owner->money > 1e4) {
            moneyButton->Text = std::to_string(static_cast<int>(owner->money / 1e3)) + "k";
        } else {
            moneyButton->Text = std::to_string(static_cast<int>(owner->money));
        }
    }
    void lateTick() override {}
    void render() override {
        moneyButton->render();
    }
    engine::config::Facade::Rect getRenderEdges() override {
        return moneyButton->getRenderEdges();
    }
    bool tryOnClick(graphics::SFMLFacade::Point, graphics::Event::MouseButton) override {
        return false;
    }
};
int main() {
    //init sockets
#ifdef WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    engine::Logger::Init(engine::Logger::SeverityLevel::TraceLevel);

    engine::config::runtime = nlohmann::json::parse(readFile("config.json"), nullptr, false, true);
    graphics::Textures::loadTextures();

    engine::config::Facade::Init(1920, 1080, "TPP2D", 60);

    auto t = util::cellGen::getMap(Point2D(15360, 8640), 10000);
    auto vec = makeSurface(t);
    for (auto ob : vec) {
        engine::gameController::Instance()->registerObject(ob);
    }

    for (int i = 0; i < Player::players.size() - 1; ++i) {
        vec[200 * i + 100]->setOwner(Player::players[i]);
        vec[200 * i + 100]->adjacent.front()->setOwner(Player::players[i]);
        vec[200 * i + 100]->adjacent.back()->setOwner(Player::players[i]);
    }

    for (auto cell : vec) {
        if(cell->owner->id == Player::players.size() - 1){
            cell->addSquad(new Squads::Squad({Units::allUnits[0]->createUnit()}));
            cell->getSquad()->setCell(cell);
        }
    }
    MoneyShower main(Player::players[engine::gameController::Instance()->networkManager.serverId]);
    engine::gameController::Instance()->registerStaticObject(&main);

    //sq2->setCell(vec[9999]);
    //engine::gameController::Instance()->registerObject(sq2);
    engine::gameController::Instance()->gameLoop();
    return 0;
}