#pragma once
#include "engine/gameObject.h"
#include "engine/actions/None.h"
#include <vector>
#ifdef WIN32
#include "winsock2.h"
#else
#include "sys/socket.h"
#endif
namespace engine {
    class NetworkManager {
      private:
        SOCKET worker;
        std::vector<gameObject*> sharedObjects;
        std::vector<size_t> freeIds;
        std::vector<std::unique_ptr<engine::Action>> pendingActions;
      public:
        uint32_t connect(std::string host, int port);

        char serverId;

        void makeShared(gameObject* obj);
        void removeShared(gameObject* obj);
        gameObject* getShared(size_t id);

        void addAction(std::unique_ptr<engine::Action> action);
        void flushActions();
        void processActions();
    };
}