#include "GameScene.h"

#include "EnemySpawner.h"
#include "Entities/Player.h"

GameScene::GameScene() noexcept
    : m_Spawner(nullptr)
{
	m_Spawner = new EnemySpawner(2.0f, 3.0f);
    CreateEntity<Player>(GetSpriteLoader().GetSprite(SpriteType::Player), 2.0f, 2.0f);
}

GameScene::~GameScene()
{
    delete m_Spawner;
}

void GameScene::Reset() noexcept
{
    Scene::Reset();
    SetGameOver(true);
	CreateEntity<Player>(GetSpriteLoader().GetSprite(SpriteType::Player), 2.0f, 2.0f);
}

DeltaTime GameScene::Update() noexcept
{
    DeltaTime deltaTime = Scene::Update();
    if (m_GameOver)
    {
        SetRenderEntities(false);
        SetUpdateEntities(false);
        m_ResetTimer.Update(deltaTime.GetDeltaTime());

		if (m_ResetTimer.IsExpired())
		{
            SetRenderEntities(true);
            SetUpdateEntities(true);
			SetGameOver(false);
			m_ResetTimer.Reset();
		}
    }
    else
    {
		m_Spawner->Update(deltaTime.GetDeltaTime());
    }

    return deltaTime;
}