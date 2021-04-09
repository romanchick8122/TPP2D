#pragma once
#include "engine/gameObject.h"
#include "engine/actions/None.h"
#include <vector>
namespace engine {
    class NetworkManager {
      private:
        std::vector<gameObject*> sharedObjects;
        std::vector<size_t> freeIds;
        std::vector<std::unique_ptr<engine::Action>> pendingActions;
      public:
        void makeShared(gameObject* obj);
        void removeShared(gameObject* obj);
        gameObject* getShared(size_t id);

        void addAction(std::unique_ptr<engine::Action> action);
        void flushActions();
        void processActions();
    };
}