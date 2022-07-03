#include "Player.h"

#include "Bullet.h"
#include "Globals.h"

#include <algorithm>
#include <cassert>

Player::Player(Sprite& sprite, int scaleX, int scaleY) noexcept
	: PhysicsEntity(sprite, scaleX, scaleY)
{
	AddTag("Player");
	SetSpeedX(5.0f);
	GetRectangle().x = (Globals::Window::Width / 2.0f) - GetRectangle().w;
	GetRectangle().y = (Globals::Window::Height - Globals::Window::Height / 6.0f) - GetRectangle().h;
}

void Player::Update()
{
	SetActiveFrameY((SDL_GetTicks() / 150) % 2);

	m_ReloadTimer.Update();
	ProcessInput();

	if (Collided())
	{
		SetCollided(false);
		Scene::GetInstance().DestroyEntity(this);
		Scene::GetInstance().Reset();
	}
}

void Player::OnCollision(const Entity& entity)
{
	if (!entity.CheckTag("Player"))
	{
		SetCollided(true);
		Scene::GetInstance().GetSoundLoader().PlaySound(SoundFXType::PlayerDied);
	}
}

void Player::ProcessInput() noexcept
{
	const uint8_t* state = SDL_GetKeyboardState(nullptr);

	if (state[SDL_SCANCODE_A])
		MoveLeft();
	else if (state[SDL_SCANCODE_D])
		MoveRight();
	else
		MoveStraight();

	if (state[SDL_SCANCODE_SPACE] && m_ReloadTimer.IsExpired())
	{
		m_ReloadTimer.Reset();
		FireBullet();
	}
}

void Player::MoveLeft() noexcept
{
	m_AnimationIdxR.Reset();
	m_AnimationIdxL.Update();
	if (m_AnimationIdxL.IsExpired())
		SetActiveFrameX(0);
	else
		SetActiveFrameX(1);

	GetRectangle().x = std::clamp(GetRectangle().x - GetSpeedX(), 0.0f, static_cast<float>(Globals::Window::Width));
}

void Player::MoveRight() noexcept
{
	m_AnimationIdxL.Reset();
	m_AnimationIdxR.Update();
	if (m_AnimationIdxR.IsExpired())
		SetActiveFrameX(4);
	else
		SetActiveFrameX(3);

	GetRectangle().x = std::clamp(GetRectangle().x + GetSpeedX(), 0.0f, static_cast<float>(Globals::Window::Width) - GetRectangle().w);
}

void Player::MoveStraight() noexcept
{
	SetActiveFrameX(2);
}

void Player::FireBullet() noexcept
{
	Bullet& bullet = Scene::GetInstance().CreateEntity<Bullet>(Scene::GetInstance().GetSpriteLoader().GetSprite(SpriteType::Bullet), 2, 2);
	bullet.Fire();
	bullet.SetSpeedY(-5.0f);
	bullet.GetRectangle().x = GetRectangle().x;
	bullet.GetRectangle().y = GetRectangle().y - bullet.GetRectangle().h;
	bullet.SetActiveFrameY(1);

	Scene::GetInstance().GetSoundLoader().PlaySound(SoundFXType::PlayerFire);
}
