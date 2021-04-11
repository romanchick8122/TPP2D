#include "AllSquadTemplates.h"
namespace Squads{
    std::vector<SquadTemplate*> AllTemplates;
}
void Squads::setDefaultSquadTemplates() {
    SquadTemplate* temp = new SquadTemplate();
    temp->addFactory(Units::allUnits[0], 1);
    AllTemplates.push_back(temp);
}
