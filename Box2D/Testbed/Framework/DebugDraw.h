/*
* Copyright (c) 2006-2013 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>


// This class implements debug drawing callbacks that are invoked
// inside b2World::Step.

class DebugDraw : public b2Draw {
 public:
    DebugDraw(sf::RenderWindow &window);
    virtual ~DebugDraw();


    virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
    virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
    virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
    virtual void DrawTransform(const b2Transform& xf);

    void DrawPoint(const b2Vec2& center, const float32& radius, const b2Color& color);
    static sf::Color B2toSFColor(const b2Color &color, int alpha);

    void DrawString(int x, int y, const char* format, ...);
    void DrawAABB(b2AABB* aabb, const b2Color& color);
    void DrawMouseJoint(b2Vec2& p1, b2Vec2& p2, const b2Color &boxColor, const b2Color &lineColor);


 private:
    const float SCALEY = -30.0f; // set to negative since demo was written for open gl coordinate system
    const float SCALEX = 30.0f;
    sf::RenderWindow* mWindow;
    std::unique_ptr<sf::Font> mFont;
};
#endif
