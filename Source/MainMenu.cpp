#include "MainMenu.h"

#include "Globals.h"
#include "Game.h"

MainMenu::MainMenu() noexcept
{
}

void MainMenu::Update(float deltaTime) noexcept
{
	Scene::Update(deltaTime);
	Game::GetInstance().GetTextRenderer().SetActiveFontSize(50);
	Game::GetInstance().GetTextRenderer().RenderText(
		"SPACE SHOOTER", 
		{ Globals::Window::Width / 2.0f, Globals::Window::Height / 2.0f - 50 },
	 	Align::Centre
	);

	FlickerText(deltaTime);

	if (!m_FlickerHidden)
	{
		Game::GetInstance().GetTextRenderer().SetActiveFontSize(24);
		Game::GetInstance().GetTextRenderer().RenderText(
			"PRESS ENTER TO PLAY",
			{ Globals::Window::Width / 2.0f, Globals::Window::Height / 2.0f + 50 },
			Align::Centre
		);
	}
}

void MainMenu::FlickerText(float deltaTime) noexcept
{
	m_FlickerTimer.Update(deltaTime);
	if (m_FlickerTimer.IsExpired())
	{
		m_FlickerHidden == true ? m_FlickerHidden = false : m_FlickerHidden = true;
		m_FlickerTimer.Reset();
	}	
}

void MainMenu::ProcessEvents(SDL_Event& event) noexcept
{
	switch (event.type)
	{
		case SDL_KEYDOWN:
			switch(event.key.keysym.scancode)
			{
				case SDL_SCANCODE_RETURN:
					if (Game::GetInstance().GetPlayerName().empty())
						Game::GetInstance().ChangeSceneTo<TextInputScene>();
					else
						Game::GetInstance().ChangeSceneTo<GameScene>();

					break;
				default: break;
			}
			break;
		
		default: break;
	}
}