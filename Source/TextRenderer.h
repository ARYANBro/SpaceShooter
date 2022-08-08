#pragma once

#include <SDL_ttf.h>

#include <string>
#include <list>

enum class Align
{
    Left, Centre, Right
};

class TextRenderer
{
public:

public:
    void SetActiveFont(const std::string& filePath, int fontSize = 24) noexcept;
    void RenderText(const std::string& text, std::pair<float, float> position, Align alignment = Align::Left, SDL_Colour colour = { .r = 255, .g = 255, .b = 255, .a = 255}) noexcept;
    void RenderQueue() noexcept;

private:

    TTF_Font* m_ActiveFont = nullptr;
    std::list<std::pair<SDL_Texture*, SDL_FRect>> m_TextRenderQueue;
};