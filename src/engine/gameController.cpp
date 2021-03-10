#include "engine/gameController.h"
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
    bool wheelPresed = false;
    int viewChangeStartX = 0;
    int viewChangeStartY = 0;
    sf::Vector2f viewChangeStartCoordShift = params.coordShift;
    while (true) {
        //restoring invariant things
        if (wheelPresed) {
            params.coordShift = viewChangeStartCoordShift;
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
                    viewChangeStartCoordShift = params.coordShift;
                }
            } else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Button::Middle) {
                    wheelPresed = false;
                    params.coordShift.x += sf::Mouse::getPosition(*window).x - viewChangeStartX;
                    params.coordShift.y += sf::Mouse::getPosition(*window).y - viewChangeStartY;
                }
            }
        }
        if (!window->isOpen()) {
            break;
        }
        //scrooling
        if (wheelPresed) {
            params.coordShift.x += sf::Mouse::getPosition(*window).x - viewChangeStartX;
            params.coordShift.y += sf::Mouse::getPosition(*window).y - viewChangeStartY;
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
            obj->render(params);
        }
        window->display();
    }
}