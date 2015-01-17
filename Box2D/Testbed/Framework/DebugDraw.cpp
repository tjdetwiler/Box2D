
#include <iostream>
#include <Box2D/Box2D.h>

#include "DebugDraw.h"
#include <SFML/Graphics.hpp>



DebugDraw::DebugDraw(sf::RenderWindow &window) {
    mWindow = &window;

}


DebugDraw::~DebugDraw() {}


void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    sf::ConvexShape polygon(vertexCount);
    for (int32 i=0; i < vertexCount; ++i) {
        b2Vec2 vertex = vertices[i];
        polygon.setPoint(i, sf::Vector2f(vertex.x * SCALEX,
                                         vertex.y * SCALEY));
    }
    polygon.setOutlineColor(DebugDraw::B2toSFColor(color, 255));
    polygon.setOutlineThickness(1.0f);
    polygon.setFillColor(sf::Color::Transparent);
    mWindow->draw(polygon);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    sf::ConvexShape polygon(vertexCount);
    for (int32 i=0; i < vertexCount; i++) {
        b2Vec2 vertex = vertices[i];
        polygon.setPoint(i, sf::Vector2f(vertex.x * SCALEX,
                                         vertex.y * SCALEY));
    }

    /* rotation indicator for rectangles */
    if (vertexCount == 4) {
        auto lineColor = DebugDraw::B2toSFColor(color, 255);
        auto a = polygon.getPoint(0);
        auto c = polygon.getPoint(2);
        auto d = polygon.getPoint(3);

        auto bottomMidPt = sf::Vector2f(d.x + (c.x - d.x) / 2.f,
                                        d.y + (c.y - d.y) / 2.f);
        auto center = sf::Vector2f(a.x + (c.x - a.x) / 2.f,
                                   a.y + (c.y - a.y) / 2.f);

        sf::Vertex line[] = {
            sf::Vertex(bottomMidPt, lineColor),
            sf::Vertex(center, lineColor)
        };

        mWindow->draw(line, 2, sf::Lines);
    }

    polygon.setOutlineColor(DebugDraw::B2toSFColor(color, 255));
    polygon.setOutlineThickness(1.0f);
    polygon.setFillColor(DebugDraw::B2toSFColor(color, 50));
    mWindow->draw(polygon);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
    sf::CircleShape circle;
    circle.setRadius(radius * SCALEX);
    circle.setOutlineColor(DebugDraw::B2toSFColor(color, 255));
    circle.setFillColor(sf::Color::Transparent);
    circle.setPosition(sf::Vector2f(center.x * SCALEX, center.y * SCALEY));
    mWindow->draw(circle);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
    sf::CircleShape circle;
    circle.setRadius(radius * SCALEX);
    circle.setOutlineColor(DebugDraw::B2toSFColor(color, 255));
    circle.setFillColor(DebugDraw::B2toSFColor(color, 50));
    circle.setPosition(sf::Vector2f(center.x * SCALEX, center.y * SCALEY));
    mWindow->draw(circle);
}


void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
    auto lineColor = DebugDraw::B2toSFColor(color, 255);

    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(SCALEX*p1.x, SCALEY*p1.y), lineColor),
        sf::Vertex(sf::Vector2f(SCALEX*p2.x, SCALEY*p2.y), lineColor)
    };

    mWindow->draw(line, 2, sf::Lines);
}

void DebugDraw::DrawPoint(const b2Vec2& center, const float32& radius, const b2Color& color) {
    DrawCircle(center, radius, color);
}


void DebugDraw::DrawTransform(const b2Transform& xf) {
    std::cerr << "DebugDraw::DrawTransform not implemented" << std::endl;
}


// convert a Box2D (float 0.0f - 1.0f range) color to a SFML color (uint8 0 - 255 range)
sf::Color DebugDraw::B2toSFColor(const b2Color &color, int alpha = 255) {
    sf::Color result((sf::Uint8)(color.r*255), (sf::Uint8)(color.g*255), (sf::Uint8)(color.b*255), (sf::Uint8) alpha);
    return result;
}


void DebugDraw::DrawMouseJoint(b2Vec2& p1, b2Vec2& p2, const b2Color &boxColor, const b2Color &lineColor) {
     std::cerr << "DebugDraw::DrawMouseJoing not implemented" << std::endl;
}

void DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& color) {
     std::cerr << "DebugDraw::DrawAABB not implemented" << std::endl;
}

void DebugDraw::DrawString(int x, int y, const char* format, ...) {



    if ( !mFont) {
        mFont.reset(new sf::Font);
        if( ! mFont->loadFromFile("./assets/font/arial.ttf") ) {
            return;
        }
    }
    
    char buffer[256];
    va_list args;
    va_start (args, format);
    vsnprintf (buffer, 255, format, args);
    std::cout << buffer << std:: endl;

// almost working, but not quite there yet
//    sf::Text text;
//    text.setString(buffer);
//    text.setFont(*mFont);
//    text.setCharacterSize(26);
//    text.setColor(sf::Color::Black);
//    text.setPosition(sf::Vector2f(x/SCALEX, y/SCALEY));
//    mWindow->draw(text);
    

}

