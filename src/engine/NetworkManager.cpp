#include <sstream>
#include "engine/NetworkManager.h"
#include <chrono>
#include <thread>
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
    std::stringstream memoryStream;
    memoryStream.put(static_cast<char>(pendingActions.size()));
    for (auto& action : pendingActions) {
        action->write(memoryStream);
    }
    pendingActions.clear();
    send(worker, memoryStream.str().c_str(), memoryStream.str().size(), 0);
}
void engine::NetworkManager::processActions() {
    char* buff = new char[16384];
    int actual = recv(worker, buff, 16384, 0);
    std::stringstream stream(std::string(buff, actual));
    delete[] buff;
    int count = stream.get();
    while (count-->0) {
        engine::readAction(stream)->apply();
    }
}

uint32_t engine::NetworkManager::connect(std::string host, int port) {
    worker = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in settings;
    settings.sin_family = AF_INET;
    settings.sin_addr.s_addr = inet_addr(host.c_str());
    settings.sin_port = htons(port);
    if(::connect(worker, (struct sockaddr*)&settings, sizeof(settings)) < 0) {
        std::system("start /b server.exe 1");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        settings.sin_family = AF_INET;
        settings.sin_addr.s_addr = inet_addr("127.0.0.1");
        settings.sin_port = htons(9587);
        if (::connect(worker, (struct sockaddr*)&settings, sizeof(settings)) < 0) {
            throw std::runtime_error("Do not close the server");
        }
    }
    char* ans = new char[6];
    recv(worker, ans, 6, 0);
    serverId = ans[0];
    int playersCount = ans[1];
    uint32_t rngSeed = *reinterpret_cast<uint32_t*>(ans + 2);
    delete[] ans;
    return rngSeed;
}