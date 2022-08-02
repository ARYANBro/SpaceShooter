#pragma once

#include "Scene.h"
#include "TextInput.h"

class TextInputScene : public Scene
{
public:
    TextInputScene() noexcept;
    virtual ~TextInputScene() noexcept override = default;

    virtual void Update(float deltaTime) noexcept override;
    virtual void Render() noexcept override;
    virtual void ProcessEvents(SDL_Event& event) noexcept override;

    const std::string& GetInputText() const noexcept { return m_InputTex; }

private:
    std::string m_InputTex;
    TextInput m_TexInput;
};