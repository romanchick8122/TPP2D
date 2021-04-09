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