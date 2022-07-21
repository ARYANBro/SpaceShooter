#pragma once

#include "TextRenderer.h"

#include <SDL2/SDL.h>

#include <string>
#include <utility>

class TextInput
{
public:
    void GetInput(std::string& outInputText, std::size_t limit = -1) { m_InputText = &outInputText; m_InputText->clear(); m_GetInput = true; m_CharLimit = limit; }
    void Render(const std::pair<float, float>& position, Align alignment = Align::Left, SDL_Colour colour = { .r = 255, .g = 255, .b = 255, .a = 255}) noexcept;
    void ProcessEvent(SDL_Event& event) noexcept;
    void EraseLastElement() noexcept;
    const std::string& GetInputText() const noexcept { return *m_InputText; }
    bool IsGettingInput() const noexcept { return m_GetInput; }

private:
    std::string* m_InputText;
    std::size_t m_CharLimit;
    bool m_GetInput = false;
};