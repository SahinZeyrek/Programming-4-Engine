#pragma once
#include "Component.h"
namespace dae
{
	class SoundComponent final : public Component
	{
	public:
		void PlaySound();

		virtual void Update() override;
		virtual void Render() override;
		//------------------------------------------------
		// RULE OF FIVE 
		//------------------------------------------------
		SoundComponent(GameObjectPtr owner);
		virtual ~SoundComponent();
		SoundComponent(const SoundComponent&) = delete;
		SoundComponent(SoundComponent&&) = delete;
		SoundComponent& operator=(const SoundComponent&) = delete;
		SoundComponent& operator=(const SoundComponent&&) = delete;
	};
}


