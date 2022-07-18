#pragma once

#include "Scene.h"
#include "HighScore.h"

class MenuScene : public Scene
{
public:
    MenuScene() noexcept;
    virtual ~MenuScene() noexcept override;
    virtual void Update(float deltaTime) noexcept override;

    const HighScoreTable& GetHighScoreTable() const noexcept { return m_HighScoreTable; }
    HighScoreTable& GetHighScoreTable() noexcept { return m_HighScoreTable; }

private:
    HighScoreTable m_HighScoreTable;

private:
    void GetPlayerName() noexcept;
};