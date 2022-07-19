#include "HighScore.h"

#include "Globals.h"
#include "Scene.h"

void HighScoreTable::TryAddHighScore(const std::string& playerName, int score) noexcept
{
    for (HighScore& h : m_HighScores)
    {
        if (h.GetScore() < score)
        {
            h.SetPlayerName(playerName);
            h.SetScore(score);
            break;
        }
    }
}

void HighScoreTable::Update(float deltaTime) noexcept
{
    for (int i = 0; i < m_HighScores.size(); i++)
    {
        std::string text = m_HighScores[i].GetPlayerName() + ": " + std::to_string(m_HighScores[i].GetScore());
        std::pair<float, float> position = { Globals::Window::Width / 3.0f, 50 * i + 50};
        Scene::GetInstance().GetTextRenderer().RenderText(text, position);
    }
}