#pragma once
#include <list>
#include "engine/gameObject.h"
namespace engine {
    class gameController {
      private:
        std::list<gameObject*> objects;
        static gameController* instance;
        gameController();
      public:
        static gameController* Instance();
        void registerObject(gameObject* object, gameObject* after = nullptr);
        void unregisterObject(gameObject* object);
        void gameLoop();
    };
}