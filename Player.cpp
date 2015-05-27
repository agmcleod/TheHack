//
//  Player.cpp
//  TheHack
//
//  Created by Aaron McLeod on 2015-05-21.
//  Copyright (c) 2015 Aaron McLeod. All rights reserved.
//

#include "Player.h"

void Player::render(Renderer &renderer) {
    renderer.renderTexture(bounds, *textureRegion->texture, textureRegion);
}

void Player::update(InputManager &im, float time) {
    if (im.isActionPressed("up")) {
        velocity.Set(0, -speed * time);
    }
    else if (im.isActionPressed("down")) {
        velocity.Set(0, speed * time);
    }
    else {
        velocity.Set(0, 0);
    }
    if (im.isActionPressed("left")) {
        velocity.Set(-speed * time, velocity.y);
    }
    else if (im.isActionPressed("right")) {
        velocity.Set(speed * time, velocity.y);
    }
    else {
        velocity.Set(0, velocity.y);
    }
    
    body->SetLinearVelocity(velocity);
    
    bounds.left = body->GetPosition().x * BOX_TO_WORLD - bounds.width / 2;
    bounds.top = body->GetPosition().y * BOX_TO_WORLD - bounds.height / 2;
}