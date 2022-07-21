#include "HighScore.h"

#include "Globals.h"
#include "Scene.h"
#include <cctype>

bool HighScoreTable::TryAddHighScore(const std::string& playerName, int score) noexcept
{
    for (HighScore& h : m_HighScores)
    {
        if (h.GetScore() < score)
        {
            h.SetPlayerName(playerName);
            h.SetScore(score);
            return true;
        }
    }

    return false;
}

void HighScoreTable::Update(float deltaTime) noexcept
{
    Scene::GetInstance().GetTextRenderer().RenderText("PLAYER", { Globals::Window::Width / 2.0f - 100, 25}, Align::Right);
    Scene::GetInstance().GetTextRenderer().RenderText("SCORE", { Globals::Window::Width / 2.0f + 100, 25}, Align::Left);

    for (int i = 0; i < m_HighScores.size(); i++)
    {
        std::string text = FormTextToDisplay(m_HighScores[i].GetPlayerName(), m_HighScores[i].GetScore());
        std::pair<float, float> position = { Globals::Window::Width / 2.0f, 50 + 50 * i + 50};
        Scene::GetInstance().GetTextRenderer().RenderText(text, position, Align::Centre);
    }
    }

std::string HighScoreTable::FormTextToDisplay(const std::string& playerName, std::size_t score, std::size_t totalTexSize) const noexcept
{
    std::string text = playerName + ' ';
    std::string textAppend = ' ' + std::to_string(score);

    while (text.size() != totalTexSize - textAppend.size())
    {
        text += '.';
    }

    text += textAppend;
    return text;
}