#pragma once
#include "engine/gameObject.h"
namespace engine::GUI {
    class GuiObject : public gameObject {
      public:
        GuiObject(engine::config::Facade::Rect fromRect);
        engine::config::Facade::Rect boundary;
    };
}