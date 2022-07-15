#pragma once

#include <SDL2/SDL_ttf.h>

#include <string>
#include <list>

class TextRenderer
{
public:
    void SetActiveFont(const std::string& filePath, int fontSize = 24) noexcept;
    void RenderText(const std::string& text, std::pair<float, float> position, SDL_Colour colour = { .r = 255, .g = 255, .b = 255, .a = 255}) noexcept;
    void RenderQueue() noexcept;

private:

    TTF_Font* m_ActiveFont = nullptr;
    std::list<std::pair<SDL_Texture*, SDL_FRect>> m_TextRenderQueue;
};