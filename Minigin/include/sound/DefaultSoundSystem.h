#pragma once

#include "ISoundSystem.h"

namespace dae
{
	class DefaultSoundSystem final : public ISoundSystem
	{
	public:
		DefaultSoundSystem();

		sound_id AddSound(std::string_view filepath) override;
		void Play(sound_id id, float volume) override;
		void Pause() override;
		void Resume() override;
		void Mute() override;
		void Unmute() override;
		void SetVolume(float volume) override;

		DefaultSoundSystem(const DefaultSoundSystem&)				= delete;
		DefaultSoundSystem(DefaultSoundSystem&&)					= delete;
		DefaultSoundSystem& operator=(const DefaultSoundSystem&)	= delete;
		DefaultSoundSystem& operator=(DefaultSoundSystem&&)			= delete;

		~DefaultSoundSystem();

	private:
		class Impl;
		Impl* m_pImpl;
	};
}
