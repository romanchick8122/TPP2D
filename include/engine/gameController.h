#pragma once
#include <list>
#include "engine/gameObject.h"
namespace engine {
    class gameController {
      private:
        std::list<gameObject*> objects;
        sf::RenderWindow* window;
      public:
        gameController(int resX, int resY, const char* windowName, int frameRate);
        void registerObject(gameObject* object);
        void unregisterObject(gameObject* object);
        void gameLoop();
    };
}