#include "BigEnemy.h"

Bullet* BigEnemy::FireBullet() noexcept
{
    Bullet* bullet1 = Enemy::FireBullet();
    Bullet* bullet2 = Enemy::FireBullet();
    Bullet* bullet3 = Enemy::FireBullet();

    bullet1->SetNext(bullet2);
    bullet2->SetNext(bullet3);

    bullet2->GetRectangle().x += 10;
    bullet3->GetRectangle().x -= 10;
    bullet2->SetSpeedX(bullet2->GetSpeedX() + 30);
    bullet3->SetSpeedX(bullet3->GetSpeedX() - 30);

    return bullet1;
}