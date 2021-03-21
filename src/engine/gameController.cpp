#include "engine/gameController.h"
#include "engine/config.h"
#include "engine/clickableGameObject.h"
using Facade = engine::config::Facade;
engine::gameController* engine::gameController::instance;
void engine::gameController::unregisterObject(gameObject* object) {
    objects.erase(object->gameObjectListPosition);
}
void engine::gameController::gameLoop() {
    engine::config::Facade::scale = 1;
    bool wheelPresed = false;
    Facade::Point viewChangeStart;
    Facade::Point viewChangeStartCoordShift = Facade::origin;
    while (true) {
        auto events = Facade::Frame();
        //restoring invariant things
        if (wheelPresed) {
            Facade::origin = viewChangeStartCoordShift;
        }
        Facade::Point cursor = Facade::mousePosition / Facade::scale + Facade::origin;
        //event processing
        for (auto event : events) {
            if (event.type == event.Close) {
                return;
            } else if (event.type == graphics::Event::MouseButtonPressed) {
                //camera movement started
                if (event.mouseButton == graphics::Event::MouseButton::Right) {
                    wheelPresed = true;
                    viewChangeStart = cursor;
                    viewChangeStartCoordShift = Facade::origin;
                }
                //left click detection
                else if (event.mouseButton == graphics::Event::MouseButton::Left) {
                    for (auto objIt = objects.rbegin(); objIt != objects.rend(); ++objIt) {
                        if (auto obj = dynamic_cast<clickableGameObject*>(*objIt)) {
                            if (!obj->getClickEdges().contains(cursor)) {
                                continue;
                            }
                            if (obj->tryOnClick(cursor)) {
                                break;
                            }
                        }
                    }
                }
            } else if (event.type == graphics::Event::MouseButtonReleased) {
                //camera movement ended
                if (event.mouseButton == graphics::Event::MouseButton::Right) {
                    wheelPresed = false;
                    Facade::origin -= cursor - viewChangeStart;
                }
            } else if (event.type == graphics::Event::MouseWheelScrolled) {
                //zooming in/out
                float oldScale = Facade::scale;
                Facade::scale += event.mouseWheelScrollDelta * config::scaleSpeed;
                if (Facade::scale > config::maxScale) {
                    Facade::scale = config::maxScale;
                } else if (Facade::scale < config::minScale) {
                    Facade::scale = config::minScale;
                }
                Facade::origin = cursor - Facade::mousePosition / Facade::scale;
            }
        }
        //camera movement
        if (wheelPresed) {
            Facade::origin -= cursor - viewChangeStart;
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
engine::gameController* engine::gameController::Instance() {
    if (instance == nullptr) {
        instance = new gameController();
    }
    return instance;
}
void engine::gameController::registerObject(engine::gameObject* object, engine::gameObject* after) {
    std::list<gameObject*>::iterator insertPos;
    if (after == nullptr) {
        insertPos = objects.end();
    } else {
        insertPos = after->gameObjectListPosition;
        insertPos++;
    }
    object->gameObjectListPosition = objects.insert(insertPos, object);
}
engine::gameController::gameController() = default;
