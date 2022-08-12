#include "Explosion.h"

#include "Sprite.h"
#include "Scene.h"
#include "SoundLoader.h"
#include "Game.h"

Explosion::Explosion(Sprite& sprite, int scaleX, int scaleY) noexcept
	: Entity(sprite, scaleX, scaleY)
{
	AddTag("Explosion");
	Game::GetInstance().GetSoundLoader().PlaySound(SoundFXType::EnemyDied);
}

void Explosion::Update(float deltaTime)
{
	m_AnimationIdx = static_cast<int>(m_Timer.GetCurrentTime() * 75) / 5;
	SetActiveFrameX(m_AnimationIdx);

	m_Timer.Update(deltaTime);
	if (m_Timer.IsExpired())
		Game::GetInstance().GetScene().DestroyEntity(this);
}