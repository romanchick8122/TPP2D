#include "engine/GUI/Button.h"
engine::GUI::Button::Button(engine::config::Facade::Rect bound, std::function<void()> click,
                            engine::config::Facade::Color col)
    : GuiObject(std::move(bound)), clickAction(click), buttonColor(col),
      buttonTexture(nullptr) {}
engine::GUI::Button::Button(engine::config::Facade::Rect bound,
                            std::function<void()> click,
                            engine::config::Facade::Texture* tex)
    : GuiObject(bound), clickAction(click), buttonTexture(tex) {}
void engine::GUI::Button::tick() {}
void engine::GUI::Button::lateTick() {}
void engine::GUI::Button::render() {
    if (buttonTexture != nullptr) {
        engine::config::Facade::DrawRect(boundary, buttonTexture);
    } else {
        engine::config::Facade::DrawRect(boundary, buttonColor);
    }
}
engine::config::Facade::Rect engine::GUI::Button::getRenderEdges() {
    return boundary;
}
bool engine::GUI::Button::tryOnClick(engine::config::Facade::Point clickPosition, graphics::Event::MouseButton button) {
    if (!boundary.contains(clickPosition)) {
        return false;
    }
    if (button == graphics::Event::MouseButton::Left) {
        clickAction();
    }
    return true;
}