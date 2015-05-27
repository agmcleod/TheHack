//
//  Player.h
//  TheHack
//
//  Created by Aaron McLeod on 2015-05-21.
//  Copyright (c) 2015 Aaron McLeod. All rights reserved.
//

#ifndef __TheHack__Player__
#define __TheHack__Player__

#include <stdio.h>
#include <Box2D/Box2D.h>
#include "GameObject.h"
#include "Texture.h"
#include "BoxRatio.h"

class Player : public GameObject {
public:
    Player(b2World &world, Texture &texture) {
        textureRegion = texture.getRegion("player.png");
        bounds = sf::FloatRect(200, 200, 32, 32);
        speed = 100.0f;
        
        b2BodyDef def;
        def.type = b2_dynamicBody;
        def.position.Set((bounds.left + bounds.width / 2) * WORLD_TO_BOX, (bounds.top + bounds.height / 2) * WORLD_TO_BOX);
        
        body = world.CreateBody(&def);
        body->SetFixedRotation(true);
        
        b2PolygonShape shape;
        shape.SetAsBox(bounds.width / 2 * WORLD_TO_BOX, bounds.height / 2 * WORLD_TO_BOX);
        
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.0f;
        body->CreateFixture(&fixtureDef);
    }
    
    virtual void render(Renderer &renderer);
    virtual void update(InputManager &im, float time);
private:
    b2Body *body;
    float speed;
    Region *textureRegion;
    b2Vec2 velocity;
    
};

#endif /* defined(__TheHack__Player__) */
