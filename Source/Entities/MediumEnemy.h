#pragma once

#include "Enemy.h"

class MediumEnemy : public Enemy
{
public:
    MediumEnemy(Sprite& sprite, int scaleX = 1, int scaleY = 1) noexcept
        : Enemy(sprite, scaleX, scaleY)
    {
        AddTag("MediumEnemy");   
    }
};