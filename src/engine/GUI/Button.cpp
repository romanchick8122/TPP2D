#include "engine/GUI/Button.h"
#include <utility>
std::string engine::GUI::Button::prepText(std::string&& str, engine::config::Facade::Rect bound, uint32_t fontSize) {
    std::vector<std::string> separated;
    std::string tmp;
    for (char c : str) {
        if (isspace(c)) {
            if (!tmp.empty()) {
                separated.push_back(tmp);
            }
            tmp = "";
        } else {
            tmp.push_back(c);
        }
    }
    if (!tmp.empty()) {
        separated.push_back(tmp);
    } else {
        int a;
    }
    int maxSymbolWidth = bound.width * 21 / fontSize / 16;
    std::string result;
    std::string line;
    int linesLeft = static_cast<int>(bound.height / fontSize);
    for (int i = 0; i < separated.size() && linesLeft > 0; ++i) {
        std::string next = line.empty() ? separated[i] : line + " " + separated[i];
        if (next.size() > maxSymbolWidth) {
            if (next == separated[i]) {
                continue;
            }
            --linesLeft;
            if (result.empty()) {
                result = line;
            } else {
                result += "\n" + line;
            }
            line = separated[i];
        } else if (i == separated.size() - 1) {
            if (result.empty()) {
                result = next;
            } else {
                result += "\n" + next;
            }
        } else {
            line = next;
        }
    }
    return result;
}
engine::GUI::Button::Button(engine::config::Facade::Rect bound, std::function<void(Button*)> click,
                            engine::config::Facade::Color col, std::string text,
                            engine::config::Facade::Color textColor, uint32_t fSize)
    : GuiObject(bound), OnClick(std::move(click)), Color(col), Texture(nullptr),
    Text(prepText(std::move(text), bound, fSize)), TextColor(textColor), fontSize(fSize) {}
engine::GUI::Button::Button(engine::config::Facade::Rect bound,
                            std::function<void(Button*)> click,
                            const engine::config::Facade::Texture* tex, std::string text,
                            engine::config::Facade::Color textColor, uint32_t fSize)
    : GuiObject(bound), OnClick(std::move(click)), Texture(tex), Text(prepText(std::move(text), bound, fSize)),
    TextColor(textColor), fontSize(fSize) {}
void engine::GUI::Button::tick() {}
void engine::GUI::Button::lateTick() {}
void engine::GUI::Button::render() {
    if (Texture != nullptr) {
        engine::config::Facade::DrawRect(boundary, Texture);
    } else {
        engine::config::Facade::DrawRect(boundary, Color);
    }
    if (!Text.empty()) {
        engine::config::Facade::DrawText(Text, fontSize, TextColor, {boundary.left, boundary.top});
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
        OnClick(this);
    }
    return true;
}