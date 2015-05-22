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

#include "GameObject.h"
#include "Texture.h"

class Player : public GameObject {
public:
    Player(Texture &texture) {
        textureRegion = texture.getRegion("player.png");
        bounds = sf::FloatRect(200, 200, 32, 32);
        speed = 250.0f;
    }
    
    virtual void render(Renderer &renderer);
    virtual void update(InputManager &im, float time);
private:
    float speed;
    Region *textureRegion;
};

#endif /* defined(__TheHack__Player__) */
