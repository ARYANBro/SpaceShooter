#include "Player.h"

#include "Game.h"
#include "Bullet.h"
#include "Globals.h"
#include "Explosion.h"
#include "SpriteLoader.h"
#include "SoundLoader.h"

#include <algorithm>
#include <cassert>
#include <iostream>

Player::Player(Sprite& sprite, int scaleX, int scaleY, const std::string& name) noexcept
	: PhysicsEntity(sprite, scaleX, scaleY), m_Name(name)
{
	AddTag("Player");
	SetSpeedX(300.0f);
	GetRectangle().x = (Globals::Window::Width / 2.0f) - GetRectangle().w;
	GetRectangle().y = Globals::Window::Height  - GetRectangle().h - 15;
}

void Player::Update(float deltaTime)
{
	SetActiveFrameY((SDL_GetTicks() / 150) % 2);

	m_ReloadTimer.Update(deltaTime);
	ProcessInput(deltaTime);

	if (Collided())
	{
		m_DeathTimer.Update(deltaTime);
		if (m_DeathTimer.IsExpired())
		{
			SetCollided(false);
			Game::GetInstance().GetScene().DestroyEntity(this);
			Game::GetInstance().GetScene().Reset();
		}
	}
}

void Player::OnCollision(const Entity& entity)
{
	if (!entity.CheckTag("Player"))
	{
		SetCollided(true);
		Game::GetInstance().GetSoundLoader().PlaySound(SoundFXType::PlayerDied);

		Sprite& sprite = Game::GetInstance().GetSpriteLoader().GetSprite(SpriteType::Explosion);
		Explosion& explosion = Game::GetInstance().GetScene().CreateEntity<Explosion>(sprite, 3, 3);
		explosion.GetRectangle().x = GetRectangle().x;
		explosion.GetRectangle().y = GetRectangle().y;
		m_DeathTimer.SetTime(explosion.GetTimer().GetTargetTime());
		Hide();
	}
}

void Player::ProcessInput(float deltaTime) noexcept
{
 	const uint8_t* state = SDL_GetKeyboardState(nullptr);

	if (state[SDL_SCANCODE_J])
		MoveLeft(deltaTime);
	else if (state[SDL_SCANCODE_L])
		MoveRight(deltaTime);
	else
		MoveStraight();

	if (state[SDL_SCANCODE_SPACE] && m_ReloadTimer.IsExpired())
	{
		m_ReloadTimer.Reset();
		FireBullet();
	}
}

void Player::MoveLeft(float deltaTime) noexcept
{
	m_AnimationIdxR.Reset();
	m_AnimationIdxL.Update(deltaTime);
	if (m_AnimationIdxL.IsExpired())
		SetActiveFrameX(0);
	else
		SetActiveFrameX(1);

	GetRectangle().x = std::clamp(GetRectangle().x - GetSpeedX() * deltaTime, 0.0f, static_cast<float>(Globals::Window::Width));
}

void Player::MoveRight(float deltaTime) noexcept
{
	m_AnimationIdxL.Reset();
	m_AnimationIdxR.Update(deltaTime);
	if (m_AnimationIdxR.IsExpired())
		SetActiveFrameX(4);
	else
		SetActiveFrameX(3);

	GetRectangle().x = std::clamp(GetRectangle().x + GetSpeedX() * deltaTime, 0.0f, static_cast<float>(Globals::Window::Width) - GetRectangle().w);
}

void Player::MoveStraight() noexcept
{
	SetActiveFrameX(2);
}

void Player::FireBullet() noexcept
{
	Bullet& bullet = Game::GetInstance().GetScene().CreateEntity<Bullet>(Game::GetInstance().GetSpriteLoader().GetSprite(SpriteType::Bullet), *this, 2, 2);
	bullet.Fire();
	bullet.SetSpeedY(-250.0f);
	bullet.GetRectangle().x = GetRectangle().x;
	bullet.GetRectangle().y = GetRectangle().y - bullet.GetRectangle().h;
	bullet.SetActiveFrameY(1);

	Game::GetInstance().GetSoundLoader().PlaySound(SoundFXType::PlayerFire);
}
