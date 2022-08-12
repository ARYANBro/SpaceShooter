#include "Game.h"
#include "GameScene.h"
#include "HighScoreScene.h"
#include "MainMenu.h"
#include "TextInputScene.h"
#include "Entities/Player.h"

template<typename SceneType> requires std::is_base_of_v<Scene, SceneType>
inline void Game::ChangeSceneTo() noexcept
{
    assert(false);
}

template<> 
inline void Game::ChangeSceneTo<HighScoreScene>() noexcept
{

    std::uint_least64_t score;
    SceneType prevType = m_Type;
    if (m_Type == SceneType::GameScene)
    {
        GameScene* gameScene = dynamic_cast<GameScene*>(m_Scene);
        if (gameScene)
            score = gameScene->GetHighScore();
    }

    m_Type = SceneType::HighScoreScene;
    delete m_Scene;
    m_Scene = new HighScoreScene();

    if (prevType == SceneType::GameScene)
        static_cast<HighScoreScene*>(m_Scene)->GetHighScoreTable().TryAddHighScore(m_PlayerName, score);
}

template<>
inline void Game::ChangeSceneTo<TextInputScene>() noexcept
{
 	m_Type = SceneType::TextInputScene;
    delete m_Scene;
    m_Scene = new TextInputScene();   
}

template<>
inline void Game::ChangeSceneTo<GameScene>() noexcept
{
    m_Type = SceneType::GameScene;
    delete m_Scene;
    m_Scene = new GameScene(m_PlayerName);
}

template<>
inline void Game::ChangeSceneTo<MainMenu>() noexcept
{
    m_Type = SceneType::MainMenu;
    delete m_Scene;
    m_Scene = new MainMenu();
}