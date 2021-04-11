#pragma once
#include "engine/GUI/GuiList.h"
#include <list>
namespace engine::GUI {
  class GuiScroll : public engine::GUI::GuiList {
    private:
      std::list<std::unique_ptr<engine::GUI::GuiObject>>::iterator viewStart;
      bool allowScrollDown;
    public:
      explicit GuiScroll(engine::config::Facade::Rect, engine::config::Facade::Color);

      void render() override;
      bool tryOnClick(engine::config::Facade::Point, graphics::Event::MouseButton) override;

      void addChild(std::unique_ptr<GuiObject>) override;
      void removeChild(GuiObject*);
  };
}