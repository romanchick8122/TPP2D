#include "engine/gameController.h"
#include "engine/config.h"
#include "engine/clickableGameObject.h"
engine::gameController::gameController(int resX, int resY, const char* windowName, int frameRate) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window = new sf::RenderWindow(sf::VideoMode(resX, resY), windowName, sf::Style::None, settings);
    window->setFramerateLimit(frameRate);
}
void engine::gameController::registerObject(gameObject* object) {
    objects.push_back(object);
    object->gameObjectListPosition = objects.end();
    --object->gameObjectListPosition;
}
void engine::gameController::unregisterObject(gameObject* object) {
    objects.erase(object->gameObjectListPosition);
}
void engine::gameController::gameLoop() {
    renderParams params;
    params.targetWindow = window;
    params.scale = 1;
    bool wheelPresed = false;
    float viewChangeStartX = 0;
    float viewChangeStartY = 0;
    sf::Vector2f viewChangeStartCoordShift = params.origin;
    while (true) {
        //restoring invariant things
        if (wheelPresed) {
            params.origin = viewChangeStartCoordShift;
        }
        float cursorX = (sf::Mouse::getPosition(*window).x) / params.scale + params.origin.x;
        float cursorY = (sf::Mouse::getPosition(*window).y) / params.scale + params.origin.y;
        //event processing
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
                break;
            } else if (event.type == sf::Event::MouseButtonPressed) {
                //camera movement started
                if (event.mouseButton.button == sf::Mouse::Button::Middle) {
                    wheelPresed = true;
                    viewChangeStartX = cursorX;
                    viewChangeStartY = cursorY;
                    viewChangeStartCoordShift = params.origin;
                }
                //left click detection
                else if (event.mouseButton.button == sf::Mouse::Button::Left) {
                    sf::Vector2f pos(cursorX, cursorY);
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
            } else if (event.type == sf::Event::MouseButtonReleased) {
                //camera movement ended
                if (event.mouseButton.button == sf::Mouse::Button::Middle) {
                    wheelPresed = false;
                    params.origin.x -= cursorX - viewChangeStartX;
                    params.origin.y -= cursorY - viewChangeStartY;
                }
            } else if (event.type == sf::Event::MouseWheelScrolled) {
                //zooming in/out
                params.scale += event.mouseWheelScroll.delta * config::scaleSpeed;
                if (params.scale > config::maxScale) {
                    params.scale = config::maxScale;
                } else if (params.scale < config::minScale) {
                    params.scale = config::minScale;
                }
            }
        }
        if (!window->isOpen()) {
            break;
        }
        //camera movement
        if (wheelPresed) {
            params.origin.x -= cursorX - viewChangeStartX;
            params.origin.y -= cursorY - viewChangeStartY;
        }
        //ticking
        for (auto obj : objects) {
            obj->tick();
        }
        for (auto obj : objects) {
            obj->lateTick();
        }
        //rendering
        window->clear(sf::Color::White);
        sf::FloatRect windowRect(params.origin,
                                 sf::Vector2f(window->getSize().x / params.scale,
                                              window->getSize().y / params.scale));
        for (auto obj : objects) {
            if (windowRect.intersects(obj->getRenderEdges())) {
                obj->render(params);
            }
        }
        window->display();
    }
}