#include "engine/gameController.h"
#include "engine/config.h"
#include "engine/clickableGameObject.h"
using Facade = engine::config::Facade;
void engine::gameController::registerObject(gameObject* object) {
    objects.push_back(object);
    object->gameObjectListPosition = objects.end();
    --object->gameObjectListPosition;
}
void engine::gameController::unregisterObject(gameObject* object) {
    objects.erase(object->gameObjectListPosition);
}
void engine::gameController::gameLoop() {
    engine::config::Facade::scale = 1;
    bool wheelPresed = false;
    float viewChangeStartX = 0;
    float viewChangeStartY = 0;
    Facade::Point viewChangeStartCoordShift = Facade::origin;
    while (true) {
        auto events = Facade::Frame();
        //restoring invariant things
        if (wheelPresed) {
            Facade::origin = viewChangeStartCoordShift;
        }
        float cursorX = (Facade::mousePosition.x) / Facade::scale + Facade::origin.x;
        float cursorY = (Facade::mousePosition.y) / Facade::scale + Facade::origin.y;
        //event processing
        for (auto event : events) {
            if (event.type == event.Close) {
                return;
            } else if (event.type == graphics::Event::MouseButtonPressed) {
                //camera movement started
                if (event.mouseButton == graphics::Event::MouseButton::Right) {
                    wheelPresed = true;
                    viewChangeStartX = cursorX;
                    viewChangeStartY = cursorY;
                    viewChangeStartCoordShift = Facade::origin;
                }
                //left click detection
                else if (event.mouseButton == graphics::Event::MouseButton::Left) {
                    Facade::Point pos(cursorX, cursorY);
                    for (auto objIt = objects.rbegin(); objIt != objects.rend(); ++objIt) {
                        if (auto obj = dynamic_cast<clickableGameObject*>(*objIt)) {
                            if (!obj->getClickEdges().contains(pos)) {
                                continue;
                            }
                            if (obj->tryOnClick(pos)) {
                                break;
                            }
                        }
                    }
                }
            } else if (event.type == graphics::Event::MouseButtonReleased) {
                //camera movement ended
                if (event.mouseButton == graphics::Event::MouseButton::Right) {
                    wheelPresed = false;
                    Facade::origin.x -= cursorX - viewChangeStartX;
                    Facade::origin.y -= cursorY - viewChangeStartY;
                }
            } else if (event.type == graphics::Event::MouseWheelScrolled) {
                //zooming in/out
                Facade::scale += event.mouseWheelScrollDelta * config::scaleSpeed;
                if (Facade::scale > config::maxScale) {
                    Facade::scale = config::maxScale;
                } else if (Facade::scale < config::minScale) {
                    Facade::scale = config::minScale;
                }
            }
        }
        //camera movement
        if (wheelPresed) {
            Facade::origin.x -= cursorX - viewChangeStartX;
            Facade::origin.y -= cursorY - viewChangeStartY;
        }
        //ticking
        for (auto obj : objects) {
            obj->tick();
        }
        for (auto obj : objects) {
            obj->lateTick();
        }
        //rendering
        Facade::Rect windowRect(Facade::origin, Facade::windowSize / Facade::scale);
        for (auto obj : objects) {
            if (windowRect.intersects(obj->getRenderEdges())) {
                obj->render();
            }
        }
    }
}