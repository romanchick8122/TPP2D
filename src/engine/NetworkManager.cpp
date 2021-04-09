#include "engine/NetworkManager.h"
void engine::NetworkManager::makeShared(gameObject* obj) {
    if (!freeIds.empty()) {
        obj->id = freeIds.back();
        freeIds.pop_back();
        sharedObjects[obj->id] = obj;
    } else {
        obj->id = sharedObjects.size();
        sharedObjects.push_back(obj);
    }
}
void engine::NetworkManager::removeShared(gameObject* obj) {
    freeIds.push_back(obj->id);
}
engine::gameObject* engine::NetworkManager::getShared(size_t id) {
    return sharedObjects[id];
}

void engine::NetworkManager::addAction(std::unique_ptr<engine::Action> action) {
    if (dynamic_cast<engine::actions::None*>(action.get())) {
        return;
    }
    pendingActions.push_back(std::move(action));
}

void engine::NetworkManager::flushActions() {
    return;
}
void engine::NetworkManager::processActions() {
    for (auto& action : pendingActions) {
        action->apply();
    }
    pendingActions.clear();
}