#include "engine/actions/SetSquadPath.h"
#include "engine/gameController.h"
engine::actions::SetSquadPath::SetSquadPath() = default;
engine::actions::SetSquadPath::SetSquadPath(Squad* squad, Cell* target) : squadId(squad->id), targetId(target->id) {}
void engine::actions::SetSquadPath::write(std::ostream& ostr) {
    ostr.put(engine::Action::Type::SetSquadPath);
    char* transformed = new char[sizeof(size_t) * 2];
    *reinterpret_cast<size_t*>(transformed) = squadId;
    *reinterpret_cast<size_t*>(transformed + sizeof(size_t)) = targetId;
    ostr.write(transformed, sizeof(size_t) * 2);
    delete[] transformed;
}
std::unique_ptr<engine::Action> engine::actions::SetSquadPath::read(std::istream& istr) {
    auto* result = new SetSquadPath;

    char* buff = new char[sizeof(size_t) * 2];
    istr.read(buff, sizeof(size_t) * 2);
    result->squadId = *reinterpret_cast<size_t*>(buff);
    result->targetId = *reinterpret_cast<size_t*>(buff + sizeof(size_t));
    delete[] buff;

    return std::unique_ptr<Action>(result);
}
void engine::actions::SetSquadPath::apply() {
    dynamic_cast<Squad*>(engine::gameController::Instance()->networkManager.getShared(squadId))->action->setPath(
        dynamic_cast<Cell*>(engine::gameController::Instance()->networkManager.getShared(targetId))
    );
}