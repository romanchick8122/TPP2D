#pragma once
#include "SFML/Graphics.hpp"
#include "Facade.h"
namespace graphics {
    class SFMLFacade {
      public:
        using Rect = sf::FloatRect;
        using Point = sf::Vector2f;
        using Color = sf::Color;
        using Texture = sf::Texture;
      private:
        static sf::RenderWindow* window;
      public:
        static float length(Point);
        static Point normalize(Point);

        static float scale;
        static Point origin;
        static Point mousePosition;
        static Point windowSize;

        static void Init(int resX, int resY, const char* windowName, int frameRate);
        static void DrawConvexPolygon(const std::vector<Point>& vertices, Color fill);
        static void DrawThickLineStrip(const std::vector<Point>& vertices, float thickness, Color fill,
                                       bool cyclic = false);
        static void DrawRect(Rect toDraw, Color fill);
        static void DrawRect(Rect toDraw, const Texture* texture);
        static void DrawText(const std::string& str, uint32_t fontSize, Color color, Point position) {
            auto text = sf::Text();
            text.setString(str);
            text.setFillColor(color);
            text.setCharacterSize(fontSize);
            text.setPosition(position);
            window->draw(text);
        }
        static std::vector<Event> Frame();
    };
}