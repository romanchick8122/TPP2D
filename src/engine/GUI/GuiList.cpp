#include "engine/GUI/GuiList.h"
engine::GUI::GuiList::GuiList(engine::config::Facade::Color color)
    : GuiObject(engine::config::Facade::Rect({0, 0}, {10, 5})), newPos(5), background(color) {}
void engine::GUI::GuiList::tick() {}
void engine::GUI::GuiList::lateTick() {}
void engine::GUI::GuiList::render() {
    engine::config::Facade::DrawRect(boundary, background);
    engine::config::Facade::origin -= {boundary.left, boundary.top};
    for (auto& nxt : children) {
        nxt->render();
    }
    engine::config::Facade::origin += {boundary.left, boundary.top};
}
bool engine::GUI::GuiList::tryOnClick(engine::config::Facade::Point clickPosition,
                                      graphics::Event::MouseButton button) {
    if (!boundary.contains(clickPosition)) {
        return false;
    }
    for (auto& nxt : children) {
        if (nxt->tryOnClick(clickPosition - engine::config::Facade::Point{boundary.left, boundary.top},
                            button)) {
            return true;
        }
    }
    return true;
}
void engine::GUI::GuiList::addChild(std::unique_ptr<GuiObject> child) {
    child->boundary.top = newPos;
    child->boundary.left = 5;
    newPos += child->boundary.height + 5;
    boundary.width = std::max(boundary.width, child->boundary.width + 10);
    boundary.height += child->boundary.height + 5;
    children.push_back(std::move(child));
}