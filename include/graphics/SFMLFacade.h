#pragma once
#include "SFML/Graphics.hpp"
#include "Facade.h"
namespace graphics {
    class SFMLFacade {
      public:
        using Rect = sf::FloatRect;
        using Point = sf::Vector2f;
        using Color = sf::Color;
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
        static std::vector<Event> Frame();
    };
}