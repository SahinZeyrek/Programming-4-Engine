#pragma once
#include "Component.h"
namespace dae
{
	class TextObject;
	class FPSComponent final : public Component
	{
	public:
		using GameObjectPtr = GameObject*;
		using TextObjectPtr = TextObject*;
		//------------------------------------------------
		// METHODS
		//------------------------------------------------
		virtual void Update() override;
		virtual void Render() override;
		TextObjectPtr GetTextureComp() const;
		//------------------------------------------------
		// RULE OF FIVE 
		//------------------------------------------------
		FPSComponent(GameObjectPtr owner, TextObjectPtr txt);
		virtual ~FPSComponent();
		FPSComponent(const FPSComponent&) = delete;
		FPSComponent(FPSComponent&&) = delete;
		FPSComponent& operator=(const FPSComponent&) = delete;
		FPSComponent& operator=(const FPSComponent&&) = delete;
	private:
		TextObjectPtr m_TextureObj;
		float m_Timer{};
		const float m_MaxTime{1.f};
		int m_FPS{};
	};


}

