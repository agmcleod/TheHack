//
//  Box2DRenderer.cpp
//  TheHack
//
//  Created by Aaron McLeod on 2015-05-23.
//  Copyright (c) 2015 Aaron McLeod. All rights reserved.
//

#include "Box2DRenderer.h"

void Box2DRenderer::setRenderer(Renderer * r) {
    this->renderer = r;
}

void Box2DRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    /* GLfloat glVertices[56];
    int offset = 0;
    for (int32 i = 0; i < vertexCount; ++i)
    {
        glVertices[offset] = vertices[i].x;
        glVertices[offset + 1] = vertices[i].y;
        glVertices[offset + 2] = color.r;
        glVertices[offset + 3] = color.g;
        glVertices[offset + 4] = color.b;
        glVertices[offset + 5] = 0.0f;
        glVertices[offset + 6] = 0.0f;
        offset += 7;
    } */
    
    GLfloat glVertices[] = {
        //  Position(2) Color(3)     Texcoords(2)
        vertices[0].x, vertices[0].y, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Top-left
        vertices[1].x, vertices[1].y, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // Top-right
        vertices[2].x, vertices[2].y, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
        vertices[3].x, vertices[3].y, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
    };
    
    GLfloat elements[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    renderer->renderBox2d(glVertices, elements);
}

void Box2DRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    /* glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
    glBegin(GL_TRIANGLE_FAN);
    for (int32 i = 0; i < vertexCount; ++i)
    {
        glVertex2f(vertices[i].x, vertices[i].y);
    }
    glEnd();
    glDisable(GL_BLEND);
    
    glColor4f(color.r, color.g, color.b, 1.0f);
    glBegin(GL_LINE_LOOP);
    for (int32 i = 0; i < vertexCount; ++i)
    {
        glVertex2f(vertices[i].x, vertices[i].y);
    }
    glEnd(); */
    DrawPolygon(vertices, vertexCount, color);
}

void Box2DRenderer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    const float32 k_segments = 16.0f;
    const float32 k_increment = 2.0f * b2_pi / k_segments;
    float32 theta = 0.0f;
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_LINE_LOOP);
    for (int32 i = 0; i < k_segments; ++i)
    {
        b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
        glVertex2f(v.x, v.y);
        theta += k_increment;
    }
    glEnd();
}

void Box2DRenderer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    const float32 k_segments = 16.0f;
    const float32 k_increment = 2.0f * b2_pi / k_segments;
    float32 theta = 0.0f;
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
    glBegin(GL_TRIANGLE_FAN);
    for (int32 i = 0; i < k_segments; ++i)
    {
        b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
        glVertex2f(v.x, v.y);
        theta += k_increment;
    }
    glEnd();
    glDisable(GL_BLEND);
    
    theta = 0.0f;
    glColor4f(color.r, color.g, color.b, 1.0f);
    glBegin(GL_LINE_LOOP);
    for (int32 i = 0; i < k_segments; ++i)
    {
        b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
        glVertex2f(v.x, v.y);
        theta += k_increment;
    }
    glEnd();
    
    b2Vec2 p = center + radius * axis;
    glBegin(GL_LINES);
    glVertex2f(center.x, center.y);
    glVertex2f(p.x, p.y);
    glEnd();
}

void Box2DRenderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
}

void Box2DRenderer::DrawTransform(const b2Transform& xf)
{
    b2Vec2 p1 = xf.p, p2;
    const float32 k_axisScale = 0.4f;
    glBegin(GL_LINES);
    
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(p1.x, p1.y);
    p2 = p1 + k_axisScale * xf.q.GetXAxis();
    glVertex2f(p2.x, p2.y);
    
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(p1.x, p1.y);
    p2 = p1 + k_axisScale * xf.q.GetYAxis();
    glVertex2f(p2.x, p2.y);
    
    glEnd();
}

void Box2DRenderer::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
    glPointSize(size);
    glBegin(GL_POINTS);
    glColor3f(color.r, color.g, color.b);
    glVertex2f(p.x, p.y);
    glEnd();
    glPointSize(1.0f);
}

void Box2DRenderer::DrawAABB(b2AABB* aabb, const b2Color& c)
{
    glColor3f(c.r, c.g, c.b);
    glBegin(GL_LINE_LOOP);
    glVertex2f(aabb->lowerBound.x, aabb->lowerBound.y);
    glVertex2f(aabb->upperBound.x, aabb->lowerBound.y);
    glVertex2f(aabb->upperBound.x, aabb->upperBound.y);
    glVertex2f(aabb->lowerBound.x, aabb->upperBound.y);
    glEnd();
}
