#pragma once
#include "engine/GUI/GuiObject.h"
namespace engine::GUI {
    class GuiStrip : public GuiObject {
      protected:
        std::vector<std::unique_ptr<GuiObject>> children;
        float layerHeight;
        float currWidth;
        float currHeight;
      public:
        engine::config::Facade::Color background;

        explicit GuiStrip(float, engine::config::Facade::Color = engine::config::Facade::Color(0, 0, 0));
        void tick() override;
        void lateTick() override;
        void render() override;
        bool tryOnClick(engine::config::Facade::Point, graphics::Event::MouseButton) override;

        void addChild(std::unique_ptr<GuiObject> child);
    };
}