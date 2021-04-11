#pragma once
#include "engine/GUI/GuiObject.h"
namespace engine::GUI {
    class Button : public GuiObject {
      public:
        std::function<void()> OnClick;
        engine::config::Facade::Texture* Texture;
        engine::config::Facade::Color Color;
        std::string Text;
        engine::config::Facade::Color TextColor;
        uint32_t fontSize;
        Button(engine::config::Facade::Rect, std::function<void()>, engine::config::Facade::Color, std::string = "",
               engine::config::Facade::Color = engine::config::Facade::Color(0, 0, 0), uint32_t = 30);
        Button(engine::config::Facade::Rect, std::function<void()>, engine::config::Facade::Texture*, std::string = "",
               engine::config::Facade::Color = engine::config::Facade::Color(0, 0, 0), uint32_t = 30);
        void tick() override;
        void lateTick() override;
        void render() override;
        engine::config::Facade::Rect getRenderEdges() override;
        bool tryOnClick(engine::config::Facade::Point, graphics::Event::MouseButton) override;
    };
}