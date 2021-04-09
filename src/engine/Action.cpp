#include "engine/Action.h"
#include "engine/actions/None.h"
#include "iostream"
std::unique_ptr<engine::Action> readAction(std::istream& istr) {
    int type = istr.get();
    if (type == engine::Action::Type::None) {
        return engine::actions::None::read(istr);
    }
}