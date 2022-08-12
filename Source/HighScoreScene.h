#pragma once

#include "Scene.h"
#include "HighScore.h"

class HighScoreScene : public Scene
{
public:
    HighScoreScene() noexcept;
    virtual ~HighScoreScene() noexcept override;
    virtual void Update(float deltaTime) noexcept override;
    virtual void ProcessEvents(SDL_Event& event) noexcept override;

    const HighScoreTable& GetHighScoreTable() const noexcept { return m_HighScoreTable; }
    HighScoreTable& GetHighScoreTable() noexcept { return m_HighScoreTable; }

private:
    HighScoreTable m_HighScoreTable;

private:
    void GetPlayerName() noexcept;
};