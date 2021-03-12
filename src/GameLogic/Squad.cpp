#include "GameLogic/Squad.h"

Squad::Squad(Cell* ptr) {
    cell = ptr;
        Unit* u = new TestUnit(this);
        units.push_back(u);
}

void Squad::tick(){
    for(Unit* unit : units) {
        unit -> tick();
    };
};
void Squad::lateTick(){return;};
void Squad::render(const renderParams& params){return;};
std::pair<sf::Vector2f , sf::Vector2f > Squad::getRenderEdges(){
    return {sf::Vector2f(), sf::Vector2f()};
};