#include "engine/GUI/Button.h"
#include <utility>
engine::GUI::Button::Button(engine::config::Facade::Rect bound, std::function<void()> click,
                            engine::config::Facade::Color col, std::string text,
                            engine::config::Facade::Color textColor, uint32_t fSize)
    : GuiObject(bound), OnClick(std::move(click)), Color(col), Texture(nullptr), Text(std::move(text)),
    TextColor(textColor), fontSize(fSize) {}
engine::GUI::Button::Button(engine::config::Facade::Rect bound,
                            std::function<void()> click,
                            engine::config::Facade::Texture* tex, std::string text,
                            engine::config::Facade::Color textColor, uint32_t fSize)
    : GuiObject(bound), OnClick(std::move(click)), Texture(tex), Text(std::move(text)), TextColor(textColor),
    fontSize(fSize) {}
void engine::GUI::Button::tick() {}
void engine::GUI::Button::lateTick() {}
void engine::GUI::Button::render() {
    if (Texture != nullptr) {
        engine::config::Facade::DrawRect(boundary, Texture);
    } else {
        engine::config::Facade::DrawRect(boundary, Color);
    }
    engine::config::Facade::DrawText(Text, fontSize, TextColor, {boundary.left, boundary.top});
}
engine::config::Facade::Rect engine::GUI::Button::getRenderEdges() {
    return boundary;
}
bool engine::GUI::Button::tryOnClick(engine::config::Facade::Point clickPosition, graphics::Event::MouseButton button) {
    if (!boundary.contains(clickPosition)) {
        return false;
    }
    if (button == graphics::Event::MouseButton::Left) {
        OnClick();
    }
    return true;
}