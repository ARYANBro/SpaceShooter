#include "MediumEnemy.h"

#include "Globals.h"

void MediumEnemy::Update(float deltaTime)
{
    Enemy::Update(deltaTime);
    GetRectangle().x += GetSpeedX() * deltaTime * std::sin(static_cast<float>(SDL_GetTicks()) / 1000 * 2) * 2;
    GetRectangle().x = std::clamp(GetRectangle().x, 0.0f, static_cast<float>(Globals::Window::Width) - GetRectangle().w);
}