#include "engine/GUI/GuiObject.h"
engine::GUI::GuiObject::GuiObject(engine::config::Facade::Rect fromRect) : boundary(std::move(fromRect)) { }