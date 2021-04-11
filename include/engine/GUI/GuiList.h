#pragma once
#include "engine/GUI/GuiObject.h"
#include <vector>
namespace engine::GUI {
    class GuiList : public GuiObject {
      protected:
        std::list<std::unique_ptr<GuiObject>> children;
        float newPos;
      public:
        engine::config::Facade::Color background;
        explicit GuiList(engine::config::Facade::Color = engine::config::Facade::Color(0, 0, 0));
        void tick() override;
        void lateTick() override;
        void render() override;
        bool tryOnClick(engine::config::Facade::Point, graphics::Event::MouseButton) override;

        virtual void addChild(std::unique_ptr<GuiObject> child);
    };
}