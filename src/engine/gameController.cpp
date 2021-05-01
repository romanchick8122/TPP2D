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
                    bool clicked = false;
                    for (auto objIt = staticObjects.rbegin(); objIt != staticObjects.rend(); ++objIt) {
                        if (auto obj = dynamic_cast<clickableGameObject*>(*objIt)) {
                            if (!obj->getClickEdges().contains(Facade::mousePosition)) {
                                continue;
                            }
                            if (obj->tryOnClick(Facade::mousePosition)) {
                                clicked = true;
                                break;
                            }
                        }
                    }
                    if (clicked) {
                        continue;
                    }
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
        for (auto obj : staticObjects) {
            obj->tick();
        }
        for (auto obj : objects) {
            obj->lateTick();
        }
        for (auto obj : staticObjects) {
            obj->lateTick();
        }
        //rendering
        Facade::Rect windowRect(Facade::origin, Facade::windowSize / Facade::scale);
        for (auto obj : objects) {
            if (windowRect.intersects(obj->getRenderEdges())) {
                obj->render();
            }
        }
        auto scaleRev = Facade::scale;
        auto originRev = Facade::origin;
        Facade::scale = 1;
        Facade::origin = Facade::Point();
        for (auto obj : staticObjects) {
            obj->render();
        }
        Facade::scale = scaleRev;
        Facade::origin = originRev;
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
void engine::gameController::registerStaticObject(engine::gameObject* object, engine::gameObject* after) {
    std::list<gameObject*>::iterator insertPos;
    if (after == nullptr) {
        insertPos = staticObjects.end();
    } else {
        insertPos = after->gameObjectListPosition;
        insertPos++;
    }
    object->gameObjectListPosition = staticObjects.insert(insertPos, object);
}
void engine::gameController::unregisterStaticObject(engine::gameObject* object) {
    staticObjects.erase(object->gameObjectListPosition);
}
engine::gameController::gameController() = default;
