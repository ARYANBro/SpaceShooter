#pragma once

#include "Scene.h"
#include "Timer.h"
#include "HighScore.h"
#include "TextInput.h"

class EnemySpawner;
class Player;

class GameScene : public Scene
{
public:
    GameScene() noexcept;
    virtual ~GameScene() noexcept override;

    virtual void Reset() noexcept override;
    virtual void Update(float deltaTime) noexcept override;
    virtual void ProcessEvents(SDL_Event& event) noexcept override;
    void ResetScore() noexcept { m_Score = 0; }

	void IncreaseScore() noexcept;
    Player* GetPlayer() noexcept;
	bool GetGameOver() const noexcept { return m_GameOver; }
    std::uint_least64_t GetScore() const noexcept { return m_Score; }

private:
	bool m_GameOver = false;
    Timer m_ResetTimer{ 2.0f };
    EnemySpawner* m_Spawner;
	std::uint_least64_t m_Score = 0;
    TextInput m_TextInput;

private:
	void SetGameOver(bool gameOver) noexcept { m_GameOver = gameOver; }
    void RenderHud() noexcept;
};