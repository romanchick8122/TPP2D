#include "engine/actions/ClickAction.h"
#include "engine/Action.h"
#include "engine/gameController.h"
#include "engine/gameplayClickableGameObject.h"

void engine::actions::ClickAction::write(std::ostream& ostr) {
    ostr.put(engine::Action::Type::None);
}
std::unique_ptr<engine::Action> engine::actions::ClickAction::read(std::istream&) {
    return std::unique_ptr<Action>(new ClickAction());
}
void engine::actions::ClickAction::apply() {
    gameplayClickableGameObject* ptr = static_cast<gameplayClickableGameObject*>(engine::gameController::Instance()->networkManager.getShared(id));
    if(ptr != nullptr) ptr -> doOnClick();
}