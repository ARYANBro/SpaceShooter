#include "Game.h"
#include "GameScene.h"
#include "TextInputScene.h"
#include "Entities/Player.h"

template<typename SceneType> requires std::is_base_of_v<Scene, SceneType>
inline void Game::ChangeSceneTo() noexcept
{
    assert(false);
}

template<> 
inline void Game::ChangeSceneTo<MenuScene>() noexcept
{
    GameScene* gameScene = static_cast<GameScene*>(m_Scene);

    std::uint_least64_t score = gameScene->GetScore();
    Player* player = gameScene->GetPlayer();

    if (player)
        m_PlayerName = player->GetName();

    m_Type = SceneType::MenuScene;
    delete m_Scene;
    m_Scene = new MenuScene();
    static_cast<MenuScene*>(m_Scene)->GetHighScoreTable().TryAddHighScore(m_PlayerName, score);
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