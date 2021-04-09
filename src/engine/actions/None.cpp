#include "engine/Action.h"
#include "engine/actions/None.h"
void engine::actions::None::write(const std::ostream& ostr) {
    ostr.put(engine::Action::Type::None);
}
void engine::actions::None::apply() {
    return;
}