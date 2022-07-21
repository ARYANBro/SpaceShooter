#include "TextInput.h"

#include "Entities/Player.h"
#include "Scene.h"

void TextInput::Render(const std::pair<float, float>& position, Align alignment, SDL_Colour colour) noexcept
{
    if (m_GetInput)
        Scene::GetInstance().GetTextRenderer().RenderText(*m_InputText, position, alignment, colour);
}

void TextInput::ProcessEvent(SDL_Event& event) noexcept
{
    if (m_GetInput)
    {
        switch (event.type)
        {
            case SDL_TEXTINPUT:
            {
                if (m_InputText->size() + 1 <= m_CharLimit)
                    *m_InputText += event.text.text;
                break;
            }

            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_BACKSPACE:
                    {
                        EraseLastElement();
                        break;
                    }

                    case SDL_SCANCODE_RETURN:
                    {
                        m_GetInput = false;
                        break;
                    }
                }

                break;
            }
        }
    }
}


void TextInput::EraseLastElement() noexcept
{                       
    if (m_InputText->size() > 0)
        m_InputText->erase(m_InputText->size() - 1);
}