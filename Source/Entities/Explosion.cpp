#include "Explosion.h"

#include "Sprite.h"
#include "Scene.h"

Explosion::Explosion(Sprite& sprite, int scaleX, int scaleY) noexcept
	: Entity(sprite, scaleX, scaleY)
{
	AddTag("Explosion");
	Scene::GetInstance().GetSoundLoader().PlaySound(SoundFXType::EnemyDied);
}

void Explosion::Update()
{
	m_AnimationIdx = (m_Timer.GetCurrentTime() / 6) % 5;
	SetActiveFrameX(m_AnimationIdx);

	m_Timer.Update();
	if (m_Timer.IsExpired())
		Scene::GetInstance().DestroyEntity(this);
}