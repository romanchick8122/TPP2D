#pragma once
#include "engine/gameObject.h"
#include "engine/config.h"
namespace engine {
    class clickableGameObject : public gameObject {
      public:
        virtual bool tryOnClick(engine::config::Facade::Point clickPosition) = 0;
        virtual engine::config::Facade::Rect getClickEdges() = 0;
    };
}