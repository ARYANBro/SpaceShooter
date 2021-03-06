#pragma once

#include "Enemy.h"

class BigEnemy : public Enemy
{
public:
    BigEnemy(Sprite& sprite, int scaleX = 1, int scaleY = 1) noexcept
        : Enemy(sprite, scaleX, scaleY, 3)
    {
        AddTag("BigEnemy"); 
    }

protected:
    Bullet* FireBullet() noexcept override;
};