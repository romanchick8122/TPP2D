#pragma once
#include <list>
#include "engine/config.h"
#include "engine/Action.h"
namespace engine {
    class gameObject {
      public:
        size_t id;
        std::list<gameObject*>::iterator gameObjectListPosition;
        virtual void tick() = 0;
        virtual void lateTick() = 0;
        virtual void render() = 0;
        virtual engine::config::Facade::Rect getRenderEdges() = 0;
        virtual bool tryOnClick(engine::config::Facade::Point clickPosition,
                                                           graphics::Event::MouseButton) = 0;
    };
}
