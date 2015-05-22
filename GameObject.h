#ifndef __TheHack_GameObject__
#define __TheHack_GameObject__

#include <stdio.h>
#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include "InputManager.h"

class GameObject {
public:
    virtual void render(Renderer &renderer) {};
    virtual void update(InputManager &im, const float time) {};
protected:
    sf::FloatRect bounds;
};

#endif /* defined(__MyPongClone__GameObject__) */
