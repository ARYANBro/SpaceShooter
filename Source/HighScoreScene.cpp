#include "HighScoreScene.h"

#include "Game.h"

#include <fstream>
#include <iostream>

static void ReadHighScores(const std::string& filePath, HighScoreTable& inTable) noexcept
{
	std::ifstream in{ filePath.c_str() };

	if (!in)
		std::cerr << "Could not open " + filePath + " HighScore.txt for reading\n";

	std::array<HighScore, 8> highScores;
	int index = 0;

	in.seekg(std::ifstream::beg);
	while (in && index < highScores.size())
	{
		int score;
		std::string playerName;
		in >> playerName >> score;
		highScores[index].SetPlayerName(playerName);
		highScores[index++].SetScore(score);
	}

	inTable.Init(highScores);
}

static void WriteHighScores(const std::string& filePath, const HighScoreTable& table)  noexcept
{
	std::ofstream out{ filePath.c_str() };

	if (!out)
		std::cerr << "Could not open " + filePath + " for writing\n";

	for (const HighScore& h : table.GetHighScores())
		out << h.GetPlayerName() << ' ' << h.GetScore() << '\n';
}

HighScoreScene::HighScoreScene() noexcept
{
    ReadHighScores("HighScore.txt", m_HighScoreTable);
}

HighScoreScene::~HighScoreScene()
{
	WriteHighScores("HighScore.txt", m_HighScoreTable);
}

void HighScoreScene::Update(float deltaTime) noexcept
{
    Scene::Update(deltaTime);

    m_HighScoreTable.Update(deltaTime);
}

void HighScoreScene::ProcessEvents(SDL_Event& event) noexcept
{
	switch (event.type)
	{
		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode)
			{
				case SDL_SCANCODE_RETURN:
					if (Game::GetInstance().GetPlayerName().empty())
						Game::GetInstance().ChangeSceneTo<TextInputScene>();
					else
						Game::GetInstance().ChangeSceneTo<GameScene>();
						
					break;
			}

			break;

		default: break;
	}
}