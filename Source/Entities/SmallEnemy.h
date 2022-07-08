#pragma once

#include "Enemy.h"

class SmallEnemy : public Enemy
{
public:
    SmallEnemy(Sprite& sprite, int scaleX = 1, int scaleY = 1) noexcept
        : Enemy(sprite, scaleX, scaleY)
    {
        AddTag("SmallEnemy");    
    }
};