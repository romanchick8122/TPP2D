#include "engine/GUI/GuiScroll.h"
engine::GUI::GuiScroll::GuiScroll(engine::config::Facade::Rect bound, engine::config::Facade::Color color)
    : GuiList(color) {
    boundary = bound;
    viewStart = children.begin();
    allowScrollDown = false;
}

void engine::GUI::GuiScroll::render() {
    engine::config::Facade::DrawRect(boundary, background);
    float awailableHeight = boundary.height - 35;
    //arrow up
    engine::config::Facade::DrawRect(engine::config::Facade::Rect({{boundary.left + 5, boundary.top + 5},
                                                                   {boundary.width - 10, 30}}),
                                     engine::config::Facade::Color(128, 255, 0));
    engine::config::Facade::origin -= {boundary.left, boundary.top};

    allowScrollDown = false;
    for (auto it = viewStart; it != children.end(); ++it) {
        auto& ptr = *it;
        if (awailableHeight < ptr->boundary.height + 40) {
            allowScrollDown = true;
            break;
        }
        ptr->boundary.left = 5;
        ptr->boundary.top = boundary.height - awailableHeight;
        awailableHeight -= ptr->boundary.height + 5;
        ptr->render();
    }
    engine::config::Facade::origin += {boundary.left, boundary.top};
    //arrow down
    engine::config::Facade::DrawRect(engine::config::Facade::Rect({{boundary.left + 5,
                                                                    boundary.top + boundary.height - 35},
                                                                   {boundary.width - 10, 30}}),
                                     engine::config::Facade::Color(128, 255, 0));
}

bool engine::GUI::GuiScroll::tryOnClick(engine::config::Facade::Point clickPosition,
                                        graphics::Event::MouseButton button) {
    if (!boundary.contains(clickPosition)) {
        return false;
    }

    //check scroll buttons
    if (clickPosition.x >= boundary.left + 5
        && clickPosition.x <= boundary.left + boundary.width - 5) {
        if (clickPosition.y >= boundary.top + 5
            && clickPosition.y <= boundary.top + 35) {
            if (viewStart != children.begin()) {
                --viewStart;
            }
            return true;
        }
        if (clickPosition.y >= boundary.top + boundary.height - 35
            && clickPosition.y <= boundary.top + boundary.height - 5) {
            if (allowScrollDown) {
                ++viewStart;
            }
            return true;
        }
    }

    float awailableHeight = boundary.height - 35;
    for (auto it = viewStart; it != children.end(); ++it) {
        auto& ptr = *it;
        if (awailableHeight < ptr->boundary.height + 40) {
            break;
        }
        ptr->boundary.left = 5;
        ptr->boundary.top = boundary.height - awailableHeight;
        awailableHeight -= ptr->boundary.height + 5;
        if (ptr->tryOnClick(clickPosition - engine::config::Facade::Point{boundary.left, boundary.top}, button)) {
            return true;
        }
    }
    return true;
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
            if (it == viewStart) {
                ++viewStart;
            }
            children.erase(it);
            return;
        }
    }
}