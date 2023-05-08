#pragma once
#include "Component.h"
#include "ResourceManager.h"
namespace dae
{
	class Texture2D;
	class Font;
	class RenderTextComponent final : public Component
	{
	public:
		//------------------------------------------------
		// METHODS
		//------------------------------------------------
		virtual void Render() override;
		virtual void Update() override;
		void SetText(const std::string& text);
		void SetTexture(const Font& font);
		Texture2D* GetTexture();
		//------------------------------------------------
		// RULE OF FIVE 
		//------------------------------------------------
		RenderTextComponent(GameObjectPtr owner, const std::string& text, std::shared_ptr<Font> font);
		~RenderTextComponent() override;
		RenderTextComponent(const RenderTextComponent&) = delete;
		RenderTextComponent(RenderTextComponent&&) = delete;
		RenderTextComponent& operator=(const RenderTextComponent&) = delete;
		RenderTextComponent& operator=(const RenderTextComponent&&) = delete;
	private: 
		
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
		bool m_needsUpdate;
		std::string m_text;
	};
}