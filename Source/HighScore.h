#pragma once

#include <array>
#include <string>

class HighScore
{
public:
    void SetPlayerName(const std::string& playerName) noexcept { m_PlayerName = playerName; }
    const std::string& GetPlayerName() const noexcept { return m_PlayerName; }
    void SetScore(int score) noexcept { m_Score = score; }
    int GetScore() const noexcept { return m_Score; }

private:
    int m_Score = 0;
    std::string m_PlayerName;
};

class HighScoreTable
{
public:
    void Init(const std::array<HighScore, 8> highScores) noexcept { m_HighScores = highScores; }

    void TryAddHighScore(const std::string& playerName, int score) noexcept;
    void Update(float deltaTime) noexcept;

    std::array<HighScore, 8>& GetHighScores() noexcept { return m_HighScores; }
    const std::array<HighScore, 8>& GetHighScores() const noexcept { return m_HighScores; }

private:
    std::array<HighScore, 8> m_HighScores;
};