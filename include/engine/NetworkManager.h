#pragma once
#include "engine/gameObject.h"
#include <vector>
namespace engine {
    class NetworkManager {
      private:
        std::vector<gameObject*> sharedObjects;
        std::vector<size_t> freeIds;
      public:
        void makeShared(gameObject* obj);
        void removeShared(gameObject* obj);
        gameObject* getShared(size_t id);
    };
}