#include "engine/GUI/GuiObject.h"
engine::GUI::GuiObject::GuiObject(engine::config::Facade::Rect fromRect) : boundary(std::move(fromRect)) { }
engine::config::Facade::Rect engine::GUI::GuiObject::getRenderEdges() {
    return boundary;
}