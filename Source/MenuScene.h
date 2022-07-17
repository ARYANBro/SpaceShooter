#pragma once

#include "Scene.h"
#include "HighScore.h"

class MenuScene : public Scene
{
public:
    MenuScene() noexcept;
    ~MenuScene() noexcept;
    virtual void Update(float deltaTime) noexcept override;

    const HighScoreTable& GetHighScoreTable() const noexcept { return m_HighScoreTable; }
    HighScoreTable& GetHighScoreTable() noexcept { return m_HighScoreTable; }

private:
    HighScoreTable m_HighScoreTable;
};