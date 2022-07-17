#include "MenuScene.h"

#include <fstream>
#include <iostream>

static void ReadHighScores(const std::string& filePath, HighScoreTable& inTable) noexcept
{
	std::ifstream in{ filePath.c_str() };

	if (!in)
		std::cerr << "Could not open " + filePath + " HighScore.txt for reading\n";

	std::array<HighScore, 8> highScores;
	int index = 0;

	while (in)
	{
		int score;
		in >> score;
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
		out << h.GetScore() << '\n';
}

MenuScene::MenuScene() noexcept
{
    ReadHighScores("HighScore.txt", m_HighScoreTable);
}

MenuScene::~MenuScene()
{
	WriteHighScores("HighScore.txt", m_HighScoreTable);
}

void MenuScene::Update(float deltaTime) noexcept
{
    Scene::Update(deltaTime);

    m_HighScoreTable.Update(deltaTime);
}
