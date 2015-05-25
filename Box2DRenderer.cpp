//
//  Box2DRenderer.cpp
//  TheHack
//
//  Created by Aaron McLeod on 2015-05-23.
//  Copyright (c) 2015 Aaron McLeod. All rights reserved.
//

#include "Box2DRenderer.h"

void Box2DRenderer::cleanup() {
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragShader);
    glDeleteShader(vertShader);
}

void Box2DRenderer::createPolygonVertices(const b2Vec2* vertices, int32 vertexCount) {
    if (vertexCount > MAX_VERTICES) {
        assert(false);
        return;
    }
    
    // convert vertices to screen resolution
    for (int i = 0; i < vertexCount; i++) {
        this->vertices[i * 2] = BOX_TO_WORLD * vertices[i].x;
        this->vertices[i * 2 + 1] = BOX_TO_WORLD * vertices[i].y;
    }
}

void Box2DRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    createPolygonVertices(vertices, vertexCount);
    drawPrimitives(eTriangles + eLines, vertexCount, color);
}

void Box2DRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    createPolygonVertices(vertices, vertexCount);
    drawPrimitives(eTriangles + eLines, vertexCount, color);
}

void Box2DRenderer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    
}

void Box2DRenderer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    
}

void Box2DRenderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    
}

void Box2DRenderer::DrawTransform(const b2Transform& xf)
{
    
}

void Box2DRenderer::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
    
}

void Box2DRenderer::drawPrimitives(uint32 primitiveTypes, uint32 aCount, const b2Color& aColor) {
    glUseProgram(shaderProgram);
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glUniform4f(colorLocation, aColor.r, aColor.g, aColor.b, 0.5f);
    
    if (primitiveTypes & eTriangles) {
        glDrawArrays(GL_TRIANGLE_FAN, 0, aCount);
    }
    
    if (primitiveTypes & eLines) {
        glDrawArrays(GL_LINE_LOOP, 0, aCount);
    }
    
    if (primitiveTypes & ePoints) {
        glUniform1f(pointSizeLocation, pointSize);
        glDrawArrays(GL_POINTS, 0, aCount);
    }
    
    glDisableVertexAttribArray(positionLocation);
    glUseProgram(0);
}

void Box2DRenderer::DrawAABB(b2AABB* aabb, const b2Color& c)
{
    
}

void Box2DRenderer::setRenderer(Renderer * r) {
    this->renderer = r;
    
    const GLchar * fragSource =
    "#version 150 core\n\
    precision mediump float;\n\
    uniform vec4 u_color;\n\
    out vec4 Color;\n\
    \n\
    void main()\n\
    {\n\
      Color = u_color;\n\
    }";
    
    const GLchar * vertSource =
    "#version 150 core\n\
    uniform mediump mat4 u_projection;\n\
    uniform mediump float u_pointSize;\n\
    in vec2 a_position;\n\
    \n\
    void main()\n\
    {\n\
      gl_PointSize = u_pointSize;\n\
      gl_Position = u_projection * vec4(a_position, 0.0, 1.0);\n\
    }";
    
    this->renderer->compileProgram(vertSource, fragSource, vertShader, fragShader, shaderProgram);
    
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "u_projection"), 1, GL_FALSE, glm::value_ptr(this->renderer->getProjectionMatrix()));
    positionLocation = glGetAttribLocation(shaderProgram, "a_position");
    colorLocation = glGetUniformLocation(shaderProgram, "u_color");
    pointSizeLocation = glGetUniformLocation(shaderProgram, "u_pointSize");
    glUseProgram(0);
}