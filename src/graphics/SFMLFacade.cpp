#include "graphics/SFMLFacade.h"
#include <cmath>
float graphics::SFMLFacade::length(graphics::SFMLFacade::Point vec) {
    return sqrtf(vec.x * vec.x + vec.y * vec.y);
}
graphics::SFMLFacade::Point graphics::SFMLFacade::normalize(graphics::SFMLFacade::Point vec) {
    return vec / length(vec);
}
sf::RenderWindow* graphics::SFMLFacade::window;
float graphics::SFMLFacade::scale;
graphics::SFMLFacade::Point graphics::SFMLFacade::origin;
graphics::SFMLFacade::Point graphics::SFMLFacade::mousePosition;
graphics::SFMLFacade::Point graphics::SFMLFacade::windowSize;
void graphics::SFMLFacade::Init(int resX, int resY, const char* windowName, int frameRate) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window = new sf::RenderWindow(sf::VideoMode(resX, resY), windowName, sf::Style::Fullscreen, settings);
    window->setFramerateLimit(frameRate);
    windowSize.x = resX;
    windowSize.y = resY;
    scale = 1;
    origin.x = origin.y = 0;
}
void graphics::SFMLFacade::DrawConvexPolygon(const std::vector<Point>& vertices, Color fill)  {
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
void graphics::SFMLFacade::DrawRect(Rect toDraw, const Texture* texture) {
    auto arr = new sf::Vertex[4];
    arr[0] = {(Point(toDraw.left, toDraw.top) - origin) * scale};
    arr[0].texCoords = {0, 0};
    arr[1] = {(Point(toDraw.left + toDraw.width, toDraw.top) - origin) * scale};
    arr[1].texCoords = {static_cast<float>(texture->getSize().x), 0};
    arr[2] = {(Point(toDraw.left + toDraw.width, toDraw.top + toDraw.height) - origin) * scale};
    arr[2].texCoords = {static_cast<float>(texture->getSize().x), static_cast<float>(texture->getSize().y)};
    arr[3] = {(Point(toDraw.left, toDraw.top + toDraw.height) - origin) * scale};
    arr[3].texCoords = {0, static_cast<float>(texture->getSize().y)};
    window->draw(arr, 4, sf::Quads, texture);
    delete[] arr;
}
void graphics::SFMLFacade::DrawThickLineStrip(const std::vector<Point>& vertices, float thickness, Color fill,
                                              bool cyclic) {
    size_t sz = cyclic ? vertices.size() + 1 : vertices.size();
    sz *= 2;
    sf::Vertex* vertexArray = new sf::Vertex[sz];
    for (size_t i = 0; i < vertices.size(); ++i) {
        Point tangent;
        if (i == 0) {
            if (!cyclic) {
                tangent = normalize(vertices[0] - vertices[1]);
            } else {
                tangent = normalize(normalize(vertices[0] - vertices[1])
                    + normalize(vertices.back()) - vertices[0]);
            }
        } else if (i == vertices.size() - 1) {
            if (!cyclic) {
                tangent = normalize(vertices[i - 1] - vertices[i]);
            } else {
                tangent = normalize(normalize(vertices[i] - vertices[0])
                    + normalize(vertices[i - 1] - vertices[i]));
            }
        } else {
            tangent = normalize(
                normalize(vertices[i] - vertices[i + 1])
                + normalize(vertices[i - 1] - vertices[i]));
        }
        tangent = Point(-tangent.y, tangent.x);
        tangent *= thickness;
        vertexArray[2 * i] = sf::Vertex((vertices[i] + tangent - origin) * scale, fill);
        vertexArray[2 * i + 1] = sf::Vertex((vertices[i] - tangent - origin) * scale, fill);
    }
    if (cyclic) {
        vertexArray[sz - 2] = vertexArray[0];
        vertexArray[sz - 1] = vertexArray[1];
    }
    window->draw(vertexArray, sz, sf::TrianglesStrip);
}
std::vector<graphics::Event> graphics::SFMLFacade::Frame() {
    window->display();
    window->clear();
    mousePosition.x = sf::Mouse::getPosition(*window).x;
    mousePosition.y = sf::Mouse::getPosition(*window).y;
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