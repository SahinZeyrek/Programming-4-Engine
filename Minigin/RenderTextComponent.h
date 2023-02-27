#pragma once
#include "Component.h"
namespace dae
{
	class TextObject;
	class RenderTextComponent final : public Component
	{
		using TextObjectPtr = TextObject*;
	public:
		//------------------------------------------------
		// METHODS
		//------------------------------------------------
		virtual void Render() override;
		virtual void Update() override;
		//------------------------------------------------
		// RULE OF FIVE 
		//------------------------------------------------
		RenderTextComponent(GameObjectPtr owner, TextObjectPtr to);
		~RenderTextComponent() override  = default;
		RenderTextComponent(const RenderTextComponent&) = delete;
		RenderTextComponent(RenderTextComponent&&) = delete;
		RenderTextComponent& operator=(const RenderTextComponent&) = delete;
		RenderTextComponent& operator=(const RenderTextComponent&&) = delete;
	private: 
		TextObjectPtr m_pTextObject{};

	};
}