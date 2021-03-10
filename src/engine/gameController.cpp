#include "engine/gameController.h"
#include "engine/config.h"
gameController::gameController(int resX, int resY, const char* windowName, int frameRate) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window = new sf::RenderWindow(sf::VideoMode(resX, resY), windowName, sf::Style::Default, settings);
    window->setFramerateLimit(frameRate);
}
void gameController::registerObject(gameObject* object) {
    objects.push_back(object);
    object->gameObjectListPosition = objects.end();
    --object->gameObjectListPosition;
}
void gameController::unregisterObject(gameObject* object) {
    objects.erase(object->gameObjectListPosition);
}
void gameController::gameLoop() {
    renderParams params;
    params.targetWindow = window;
    params.scale = 1;
    bool wheelPresed = false;
    int viewChangeStartX = 0;
    int viewChangeStartY = 0;
    sf::Vector2f viewChangeStartCoordShift = params.origin;
    while (true) {
        //restoring invariant things
        if (wheelPresed) {
            params.origin = viewChangeStartCoordShift;
        }
        //event processing
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
                break;
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Button::Middle) {
                    wheelPresed = true;
                    viewChangeStartX = event.mouseButton.x;
                    viewChangeStartY = event.mouseButton.y;
                    viewChangeStartCoordShift = params.origin;
                }
            } else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Button::Middle) {
                    wheelPresed = false;
                    params.origin.x -= (sf::Mouse::getPosition(*window).x - viewChangeStartX) / params.scale;
                    params.origin.y -= (sf::Mouse::getPosition(*window).y - viewChangeStartY) / params.scale;
                }
            } else if (event.type == sf::Event::MouseWheelScrolled) {
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
        //scrooling
        if (wheelPresed) {
            params.origin.x -= (sf::Mouse::getPosition(*window).x - viewChangeStartX) / params.scale;
            params.origin.y -= (sf::Mouse::getPosition(*window).y - viewChangeStartY) / params.scale;
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
        for (auto obj : objects) {
            auto edges = obj->getRenderEdges();
            if (edges.second.x < params.origin.x
                || edges.second.y < params.origin.y
                || edges.first.x > params.origin.x + window->getSize().x / params.scale
                || edges.first.y > params.origin.y + window->getSize().y / params.scale) {
                continue;
            }
            obj->render(params);
        }
        window->display();
    }
}