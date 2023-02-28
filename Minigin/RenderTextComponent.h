#pragma once
#include "Component.h"
#include "ResourceManager.h"
namespace dae
{
	class TextObject;
	class Font;
	class RenderTextComponent final : public Component
	{
		using TextObjectPtr = TextObject*;
	public:
		//------------------------------------------------
		// METHODS
		//------------------------------------------------
		virtual void Render() override;
		virtual void Update() override;
		void SetTexture(const Font& font);
		TextObjectPtr GetTexture();
		//------------------------------------------------
		// RULE OF FIVE 
		//------------------------------------------------
		RenderTextComponent(GameObjectPtr owner, TextObjectPtr to);
		~RenderTextComponent() override;
		RenderTextComponent(const RenderTextComponent&) = delete;
		RenderTextComponent(RenderTextComponent&&) = delete;
		RenderTextComponent& operator=(const RenderTextComponent&) = delete;
		RenderTextComponent& operator=(const RenderTextComponent&&) = delete;
	private: 
		TextObjectPtr m_pTextObject{};

	};
}