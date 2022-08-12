#include "TextRenderer.h"

#include "Globals.h"
#include "Sprite.h"
#include "Entities/Entity.h"

static void RenderTexture(SDL_Texture* texture, SDL_Rect* texRect, const SDL_FRect& rectangle) noexcept
{
	SDL_RenderCopyF(Globals::Renderer::Renderer, texture, texRect, &rectangle);
}

static void RenderSprite(Sprite& sprite, const SDL_FRect& rect) noexcept
{
	RenderTexture(sprite.GetTexture(), &sprite.GetRectangle(), rect);
}

static void Render(Entity& entity) noexcept
{
	entity.GetSprite().SetFrameX(entity.GetActiveFrameX());
	entity.GetSprite().SetFrameY(entity.GetActiveFrameY());
	RenderSprite(entity.GetSprite(), entity.GetRectangle());
}

void TextRenderer::SetActiveFont(const std::string& filePath, int fontSize) noexcept
{
    if (m_ActiveFont != nullptr)
        TTF_CloseFont(m_ActiveFont);

    m_FontPath = filePath;
    m_ActiveFont = TTF_OpenFont(m_FontPath.c_str(), fontSize);
}

void TextRenderer::SetActiveFontSize(int fontSize) noexcept
{
    if (m_ActiveFont != nullptr)
        TTF_CloseFont(m_ActiveFont);

    m_ActiveFont = TTF_OpenFont(m_FontPath.c_str(), fontSize);
}

void TextRenderer::RenderText(const std::string& text, std::pair<float, float> position, Align alignment, SDL_Colour colour) noexcept
{
    SDL_Surface* surface = TTF_RenderText_Blended(m_ActiveFont, text.c_str(), colour);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Globals::Renderer::GetRenderer(), surface);
    SDL_FreeSurface(surface);

    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    SDL_FRect rect = {
        .x = position.first,
        .y = position.second,
        .w = static_cast<float>(w),
        .h = static_cast<float>(h)
    };


    switch (alignment)
    {
        case Align::Left:
        break;

        case Align::Centre:
        rect.x -= w / 2.0f;
        break;

        case Align::Right:
        rect.x -= w;
        break;
    }

    m_TextRenderQueue.push_back({ texture, rect });
}

void TextRenderer::RenderQueue() noexcept
{
    for (auto& t : m_TextRenderQueue)
    {
        RenderTexture(t.first, nullptr, t.second);
        SDL_DestroyTexture(t.first);
    }

    m_TextRenderQueue.clear();
}