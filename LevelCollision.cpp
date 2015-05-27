//
//  LevelCollision.cpp
//  TheHack
//
//  Created by Aaron McLeod on 2015-05-26.
//  Copyright (c) 2015 Aaron McLeod. All rights reserved.
//

#include <stdio.h>
#include "LevelCollision.h"

void LevelCollision::buildWorldCollision(b2World &world) {
    
    std::vector<b2Vec2> points = {
        b2Vec2(0, 200 * WORLD_TO_BOX), b2Vec2(0, 280 * WORLD_TO_BOX),
        b2Vec2(200 * WORLD_TO_BOX, 85 * WORLD_TO_BOX), b2Vec2(200 * WORLD_TO_BOX, 0)
    };
    buildPolygonBody(points, world);
    
    points = {
        b2Vec2(200 * WORLD_TO_BOX, 0), b2Vec2(600 * WORLD_TO_BOX, 0),
        b2Vec2(600 * WORLD_TO_BOX, 85 * WORLD_TO_BOX), b2Vec2(200 * WORLD_TO_BOX, 85 * WORLD_TO_BOX)
    };
    buildPolygonBody(points, world);
    
    points = {
        b2Vec2(600 * WORLD_TO_BOX, 0), b2Vec2(600 * WORLD_TO_BOX, 85 * WORLD_TO_BOX),
        b2Vec2(800 * WORLD_TO_BOX, 285 * WORLD_TO_BOX), b2Vec2(800 * WORLD_TO_BOX, 200 * WORLD_TO_BOX)
    };
    buildPolygonBody(points, world);
}

void LevelCollision::buildPolygonBody(const std::vector<b2Vec2> &points, b2World &world) {
    b2BodyDef def;
    def.type = b2_staticBody;
    
    b2Body *body = world.CreateBody(&def);
    
    b2PolygonShape shape;
    const b2Vec2 *p = &points[0];
    shape.Set(p, 4);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    body->CreateFixture(&fixtureDef);
}