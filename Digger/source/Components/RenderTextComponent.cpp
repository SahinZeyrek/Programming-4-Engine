#include "RenderTextComponent.h"
#include "Font.h"
#include "Renderer.h"
#include <SDL_ttf.h>
#include "Texture2D.h"
#include <stdexcept>
namespace dae
{
	RenderTextComponent::RenderTextComponent(GameObjectPtr owner, const std::string& text, std::shared_ptr<Font> font) : Component(owner)
	{
		m_text = text;
		m_font = std::move(font);
		m_needsUpdate = true;
		m_textTexture = nullptr;
	}
	RenderTextComponent::~RenderTextComponent()
	{
		
	}
	void RenderTextComponent::Render()
	{
		if (m_textTexture != nullptr)
		{
			const auto& pos = GetOwnerPosition();
			Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
		}
	}

	void RenderTextComponent::Update()
	{
		if (m_needsUpdate)
		{
			const SDL_Color color = { 0,255,0 }; // only white text is supported now
			const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
			if (surf == nullptr)
			{
				throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
			}
			auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
			if (texture == nullptr)
			{
				throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
			}
			SDL_FreeSurface(surf);
			m_textTexture = std::make_shared<Texture2D>(texture);
			m_needsUpdate = false;
		}
	}

	void RenderTextComponent::SetText(const std::string& text)
	{
		m_text = text;
		m_needsUpdate = true;
	}

	void RenderTextComponent::SetTexture(const Font& font)
	{
		font;
	}

	Texture2D* RenderTextComponent::GetTexture()
	{
		return m_textTexture.get();
	}
	
}

