#include "TextInputScene.h"

#include "Globals.h"

TextInputScene::TextInputScene() noexcept
{
    m_TexInput.GetInput(m_InputTex, 10);
}

void TextInputScene::Update(float deltaTime) noexcept
{
    Scene::Update(deltaTime);
}

void TextInputScene::Render() noexcept
{
    Scene::Render();
    Scene::GetTextRenderer().RenderText("ENTER PLAYER NAME BELOW:", { Globals::Window::Width / 2.0f, 120 }, Align::Centre);
    Scene::GetTextRenderer().RenderText("PRESS ENTER WHEN FINISHED", { Globals::Window::Width / 2.0f, 450 }, Align::Centre);
    m_TexInput.Render({ Globals::Window::Width / 2.0f, Globals::Window::Height / 2.0f }, Align::Centre);
}

void TextInputScene::ProcessEvents(SDL_Event& event) noexcept
{
    m_TexInput.ProcessEvent(event);
}