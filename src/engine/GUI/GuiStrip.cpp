#include "engine/GUI/GuiStrip.h"
engine::GUI::GuiStrip::GuiStrip(float maxWidth, engine::config::Facade::Color color)
    : GuiObject(engine::config::Facade::Rect({0, 0}, {maxWidth, 10})), background(color),
      layerHeight(0),
      currWidth(5), currHeight(5) {}
void engine::GUI::GuiStrip::tick() {}
void engine::GUI::GuiStrip::lateTick() {}
void engine::GUI::GuiStrip::render() {
    engine::config::Facade::DrawRect(boundary, background);
    engine::config::Facade::origin -= {boundary.left, boundary.top};
    for (auto& nxt : children) {
        nxt->render();
    }
    engine::config::Facade::origin += {boundary.left, boundary.top};
}
bool engine::GUI::GuiStrip::tryOnClick(engine::config::Facade::Point clickPosition,
                                       graphics::Event::MouseButton button) {
    if (!boundary.contains(clickPosition)) {
        return false;
    }
    return true;
}
void engine::GUI::GuiStrip::addChild(std::unique_ptr<GuiObject> child) {
    if (child->boundary.width + currWidth + 5 > boundary.width) {
        currHeight += layerHeight + 5;
        layerHeight = 0;
        currWidth = 5;
    }
    layerHeight = std::max(layerHeight, child->boundary.height);
    boundary.height = currHeight + layerHeight + 5;
    child->boundary.left = currWidth;
    currWidth += child->boundary.width + 5;
    child->boundary.top = currHeight;
    children.push_back(std::move(child));
}
