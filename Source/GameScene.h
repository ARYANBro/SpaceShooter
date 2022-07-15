#pragma once

#include "Scene.h"
#include "Timer.h"

class EnemySpawner;

class GameScene : public Scene
{
public:
    GameScene() noexcept;
    ~GameScene() noexcept;

    virtual void Reset() noexcept override;
    virtual DeltaTime Update() noexcept override;

	void IncreaseScore() noexcept;
	bool GetGameOver() const noexcept { return m_GameOver; }

private:
	bool m_GameOver = false;
    Timer m_ResetTimer{ 2.0f };
    EnemySpawner* m_Spawner;

private:
	void SetGameOver(bool gameOver) noexcept { m_GameOver = gameOver; }
};