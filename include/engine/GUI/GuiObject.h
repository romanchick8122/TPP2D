#pragma once
#include "engine/gameObject.h"
namespace engine::GUI {
    class GuiObject : public gameObject {
      public:
        explicit GuiObject(engine::config::Facade::Rect fromRect);
        engine::config::Facade::Rect boundary;
        engine::config::Facade::Rect getRenderEdges() override;
    };
}