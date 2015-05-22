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
        bounds.top -= speed * time;
    }
    else if (im.isActionPressed("down")) {
        bounds.top += speed * time;
    }
    if (im.isActionPressed("left")) {
        bounds.left -= speed * time;
    }
    else if (im.isActionPressed("right")) {
        bounds.left += speed * time;
    }
}