#pragma once

#include "Scene.h"

#include "Timer.h"

class MainMenu : public Scene
{
public:
	MainMenu() noexcept;
	virtual void Update(float deltaTime) noexcept;
	virtual void ProcessEvents(SDL_Event& event) noexcept override;

private:
	Timer m_FlickerTimer = Timer(0.6f);
	bool m_FlickerHidden;

private:
	void FlickerText(float deltaTime) noexcept;
};