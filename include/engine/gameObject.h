#pragma once
#include "engine/renderParams.h"
#include <list>
namespace engine {
    class gameObject {
      public:
        std::list<gameObject*>::iterator gameObjectListPosition;
        virtual void tick() = 0;
        virtual void lateTick() = 0;
        virtual void render(const renderParams& params) = 0;
        virtual sf::FloatRect getRenderEdges() = 0;
    };
}