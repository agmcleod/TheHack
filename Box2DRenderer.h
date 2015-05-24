//
//  Box2DRenderer.h
//  TheHack
//
//  Created by Aaron McLeod on 2015-05-23.
//  Copyright (c) 2015 Aaron McLeod. All rights reserved.
//

#ifndef __TheHack__Box2DRenderer__
#define __TheHack__Box2DRenderer__

#include <stdio.h>
#include <Box2D/Box2D.h>
#include "Renderer.h"

class Box2DRenderer : public b2Draw {
public:
    void setRenderer(Renderer * r);
    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
    void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
    void DrawTransform(const b2Transform& xf);
    void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
    void DrawAABB(b2AABB* aabb, const b2Color& color);
private:
    Renderer *renderer;
};

#endif /* defined(__TheHack__Box2DRenderer__) */
