#include "engine/actions/ClickAction.h"
#include "engine/Action.h"

void engine::actions::ClickAction::write(std::ostream& ostr) {
    ostr.put(engine::Action::Type::None);
}
std::unique_ptr<engine::Action> engine::actions::ClickAction::read(std::istream&) {
    return std::unique_ptr<Action>(new ClickAction());
}
void engine::actions::ClickAction::apply() {
    return;
}