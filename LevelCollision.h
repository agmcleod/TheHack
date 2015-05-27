//
//  level_collision.h
//  TheHack
//
//  Created by Aaron McLeod on 2015-05-26.
//  Copyright (c) 2015 Aaron McLeod. All rights reserved.
//

#ifndef TheHack_level_collision_h
#define TheHack_level_collision_h

#include <Box2D/Box2D.h>
#include "BoxRatio.h"
#include <vector>

class LevelCollision {
public:
    LevelCollision() {}
    void buildWorldCollision(b2World &world);
    void buildPolygonBody(const std::vector<b2Vec2> &points, b2World &world);
};



#endif
