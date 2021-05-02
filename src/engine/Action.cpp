#include "engine/Action.h"
#include "engine/actions/None.h"
#include "engine/actions/SetSquadPath.h"
#include "engine/actions/SpawnAction.h"
#include "engine/gameController.h"
#include "iostream"
std::unique_ptr<engine::Action> engine::readAction(std::istream& istr) {
    int type = istr.get();
    if (type == engine::Action::Type::None) {
        return engine::actions::None::read(istr);
    } else if (type == engine::Action::Type::SetSquadPath) {
        return engine::actions::SetSquadPath::read(istr);
    } else if (type == engine::Action::Type::SpawnAction) {
        return engine::actions::SpawnAction::read(istr);
    }
    return std::unique_ptr<engine::Action>(nullptr);
}