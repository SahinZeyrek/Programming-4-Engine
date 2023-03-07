#pragma once
#include "Component.h"
namespace dae
{
	class RenderTextComponent;
	class FPSComponent final : public Component
	{
	public:
		using GameObjectPtr = GameObject*;
		using TextCompPtr = RenderTextComponent*;
		//------------------------------------------------
		// METHODS
		//------------------------------------------------
		virtual void Update() override;
		virtual void Render() override;
		TextCompPtr GetTextureComp() const;
		//------------------------------------------------
		// RULE OF FIVE 
		//------------------------------------------------
		FPSComponent(GameObjectPtr owner);
		virtual ~FPSComponent();
		FPSComponent(const FPSComponent&) = delete;
		FPSComponent(FPSComponent&&) = delete;
		FPSComponent& operator=(const FPSComponent&) = delete;
		FPSComponent& operator=(const FPSComponent&&) = delete;
	private:
		TextCompPtr m_TextComp;
		float m_Timer{};
		const float m_MaxTime{1.f};
		int m_FPS{};
	};


}

