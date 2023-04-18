#pragma once
#include "Observer.h"
#include "RenderTextComponent.h"
#include "HealthComponent.h"
namespace dae
{
	class UIComponent final : public Component,public Observer
	{
	public:
		using GameObjectPtr = GameObject*;
		using TextCompPtr = RenderTextComponent*;
		using HealtCompPtr = HealthComponent*;
		//------------------------------------------------
		// METHODS
		//------------------------------------------------
		virtual void Update() override;
		virtual void Render() override;
		virtual void OnEvent(Event e) override;
		TextCompPtr GetTextureComp() const;
		//------------------------------------------------
		// RULE OF FIVE 
		//------------------------------------------------
		UIComponent(GameObjectPtr owner, GameObjectPtr target);
		virtual ~UIComponent();
		UIComponent(const UIComponent&) = delete;
		UIComponent(UIComponent&&) = delete;
		UIComponent& operator=(const UIComponent&) = delete;
		UIComponent& operator=(const UIComponent&&) = delete;
	private:
		TextCompPtr m_TextRender{};
		HealtCompPtr m_HealthComp{};
	};
}


