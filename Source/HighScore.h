#pragma once
#include <array>

class HighScore
{
public:
    void SetScore(int score) noexcept { m_Score = score; }
    int GetScore() const noexcept { return m_Score; }

private:
    int m_Score = 0;
};

class HighScoreTable
{
public:
    void Init(const std::array<HighScore, 8> highScores) noexcept { m_HighScores = highScores; }

    void TryAddHighScore(int score) noexcept;
    void Update(float deltaTime) noexcept;

    std::array<HighScore, 8>& GetHighScores() noexcept { return m_HighScores; }
    const std::array<HighScore, 8>& GetHighScores() const noexcept { return m_HighScores; }

private:
    std::array<HighScore, 8> m_HighScores;
};