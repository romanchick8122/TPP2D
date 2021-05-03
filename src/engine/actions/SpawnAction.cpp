#include "engine/actions/SpawnAction.h"
#include "GameLogic/Units/Factory.h"
#include <utility>
#include "engine/Logger.h"
engine::actions::SpawnAction::SpawnAction(std::vector<std::pair<size_t, size_t>>&& constructFrom, size_t _buildOn,
                                          char _owner)
    : factories(std::move(constructFrom)), buildOn(_buildOn), owner(_owner) { }
void engine::actions::SpawnAction::write(std::ostream& ostr) {
    ostr.put(engine::Action::SpawnAction);
    ostr.put(owner);
    ostr.write(reinterpret_cast<char*>(&buildOn), sizeof(size_t));
    auto size = factories.size();
    ostr.write(reinterpret_cast<char*>(&size), sizeof(size_t));
    ostr.write(reinterpret_cast<char*>(factories.data()), size * sizeof(size_t) * 2);
}
std::unique_ptr<engine::Action> engine::actions::SpawnAction::read(std::istream& istr) {
    char _owner;
    istr.get(_owner);
    size_t size, _buildOn;
    istr.read(reinterpret_cast<char*>(&_buildOn), sizeof(size_t));
    istr.read(reinterpret_cast<char*>(&size), sizeof(size_t));
    std::vector<std::pair<size_t, size_t>> resFactories;
    resFactories.resize(size);
    istr.read(reinterpret_cast<char*>(resFactories.data()), size * sizeof(size_t) * 2);
    return std::unique_ptr<engine::Action>(new SpawnAction(std::move(resFactories), _buildOn, _owner));
}
void engine::actions::SpawnAction::apply() {
    std::string loggerString = "Spawn action: ";

    float price = 0;
    std::list<Units::Unit*> units_;
    for(auto f : factories) {
        loggerString += "(" + std::to_string(f.first) + "; " + std::to_string(f.second) + ")";
        auto factory = dynamic_cast<Factory*>(engine::gameController::Instance()->networkManager.getShared(f.first));
        price += factory->cost * static_cast<float>(f.second);
        for (size_t i = 0; i < f.second; ++i) {
            units_.push_back(factory->createUnit());
        }
    }
    if (price > Player::players[owner]->money) {
        return;
    }
    engine::Logger::Trace(loggerString);
    Player::players[owner]->money -= price;
    auto spawnedSquad = new Squads::Squad(units_);
    spawnedSquad->setCell(dynamic_cast<Cell*>(engine::gameController::Instance()->networkManager.getShared(buildOn)));
    spawnedSquad->setOwner(Player::players[owner]);
}