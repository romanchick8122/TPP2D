#include "engine/GUI/GuiScroll.h"
engine::GUI::GuiScroll::GuiScroll(engine::config::Facade::Rect bound, engine::config::Facade::Color color)
    : GuiList(color) {
    boundary = bound;
    viewStart = children.begin();
    allowScrollDown = false;
}

void engine::GUI::GuiScroll::render() {
    engine::config::Facade::DrawRect(boundary, background);
    float awailableHeight = boundary.height - 20;
    //arrow up
    engine::config::Facade::DrawRect(engine::config::Facade::Rect({{boundary.left + 5, boundary.top + 5},
                                                                   {boundary.width - 10, 30}}),
                                     engine::config::Facade::Color(128, 255, 0));
    engine::config::Facade::origin -= {boundary.left, boundary.top};
    for (auto it = viewStart; it != children.end(); ++it) {
        auto& ptr = *it;
        if (awailableHeight < ptr->boundary.height + 40) {
            break;
        }
        ptr->boundary.left = 5;
        ptr->boundary.top = boundary.height - awailableHeight;
        awailableHeight -= ptr->boundary.height + 5;
        ptr->render();
    }
    engine::config::Facade::origin += {boundary.left, boundary.top};
    //arrow down
    engine::config::Facade::DrawRect(engine::config::Facade::Rect({{boundary.left+5, boundary.top+boundary.height-35},
                                                                   {boundary.width - 10, 30}}),
                                     engine::config::Facade::Color(128, 255, 0));
}

void engine::GUI::GuiScroll::addChild(std::unique_ptr<GuiObject> child) {
    children.push_back(std::move(child));
    if (viewStart == children.end()) {
        viewStart = children.begin();
    }
}
void engine::GUI::GuiScroll::removeChild(GuiObject* obj) {
    for (auto it = children.begin(); it != children.end(); ++it) {
        if (it->get() == obj) {
            children.erase(it);
            return;
        }
    }
}