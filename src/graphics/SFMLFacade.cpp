#include "graphics/SFMLFacade.h"
sf::RenderWindow* graphics::SFMLFacade::window;
float graphics::SFMLFacade::scale;
graphics::SFMLFacade::Point graphics::SFMLFacade::origin;
graphics::SFMLFacade::Point graphics::SFMLFacade::mousePosition;
graphics::SFMLFacade::Point graphics::SFMLFacade::windowSize;
void graphics::SFMLFacade::Init(int resX, int resY, const char* windowName, int frameRate) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window = new sf::RenderWindow(sf::VideoMode(resX, resY), windowName, sf::Style::None, settings);
    window->setFramerateLimit(frameRate);
    windowSize.x = resX;
    windowSize.y = resY;
    scale = 1;
    origin.x = origin.y = 0;
}
void graphics::SFMLFacade::DrawConvexPolygon(const std::vector<Point> vertices, Color fill)  {
    auto* vertexArray = new sf::Vertex[vertices.size()];
    for (size_t i = 0; i < vertices.size(); ++i) {
        vertexArray[i] = sf::Vertex((vertices[i] - origin) * scale, fill);
    }
    window->draw(vertexArray, vertices.size(), sf::TriangleFan);
    delete[] vertexArray;
}
void graphics::SFMLFacade::DrawRect(Rect toDraw, Color fill) {
    auto arr = new sf::Vertex[4];
    arr[0] = {(Point(toDraw.left, toDraw.top) - origin) * scale, fill};
    arr[1] = {(Point(toDraw.left + toDraw.width, toDraw.top) - origin) * scale, fill};
    arr[2] = {(Point(toDraw.left + toDraw.width, toDraw.top + toDraw.height) - origin) * scale, fill};
    arr[3] = {(Point(toDraw.left, toDraw.top + toDraw.height) - origin) * scale, fill};
    window->draw(arr, 4, sf::Quads);
    delete[] arr;
}
std::vector<graphics::Event> graphics::SFMLFacade::Frame() {
    window->display();
    window->clear();
    mousePosition.x = sf::Mouse::getPosition().x;
    mousePosition.y = sf::Mouse::getPosition().y;
    sf::Event e;
    std::vector<Event> ans;
    while (window->pollEvent(e)) {
        bool needButtonParse = false;
        if (e.type == sf::Event::Closed) {
            ans.emplace_back(Event::Type::Close);
        } else if (e.type == sf::Event::MouseButtonPressed) {
            ans.emplace_back(Event::Type::MouseButtonPressed);
            needButtonParse = true;
        } else if (e.type == sf::Event::MouseButtonReleased) {
            ans.emplace_back(Event::Type::MouseButtonReleased);
            needButtonParse = true;
        } else if (e.type == sf::Event::MouseWheelScrolled) {
            ans.emplace_back(Event::Type::MouseWheelScrolled);
            ans.back().mouseWheelScrollDelta = e.mouseWheelScroll.delta;
        }

        if (needButtonParse) {
            switch (e.mouseButton.button) {
                case sf::Mouse::Button::Left:
                    ans.back().mouseButton = Event::MouseButton::Left;
                    break;
                case sf::Mouse::Button::Right:
                    ans.back().mouseButton = Event::MouseButton::Right;
                    break;
                case sf::Mouse::Button::Middle:
                    ans.back().mouseButton = Event::MouseButton::Middle;
                    break;
                case sf::Mouse::XButton1:
                case sf::Mouse::XButton2:
                case sf::Mouse::ButtonCount:
                    throw std::runtime_error("Unsupported button");
            }
        }
    }
    return ans;
}