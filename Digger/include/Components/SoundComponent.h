#pragma once

#include "Component.h"
#include "sound/ISoundSystem.h"

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
		SoundComponent(GameObjectPtr owner, std::string_view soundPath, float volume);
		virtual ~SoundComponent() = default;
		SoundComponent(const SoundComponent&) = delete;
		SoundComponent(SoundComponent&&) = delete;
		SoundComponent& operator=(const SoundComponent&) = delete;
		SoundComponent& operator=(const SoundComponent&&) = delete;

	private:
		sound_id m_SoundId;
		float m_Volume;
	};
}


