#include "engine/Action.h"
#include "engine/actions/None.h"
void engine::actions::None::write(std::ostream& ostr) {
    ostr.put(engine::Action::Type::None);
}
std::unique_ptr<engine::Action> engine::actions::None::read(std::istream&) {
    return std::unique_ptr<Action>(new None());
}
void engine::actions::None::apply() {
    return;
}