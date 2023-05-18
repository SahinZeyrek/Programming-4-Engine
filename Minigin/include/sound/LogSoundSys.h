#pragma once
#include "ISoundSystem.h"
#include <memory>
namespace dae
{
	class LogSoundSys final : public ISoundSystem
	{
		std::unique_ptr<ISoundSystem> m_realSS;
	public:
		LogSoundSys(std::unique_ptr<ISoundSystem>&& sys);

		sound_id AddSound(std::string_view filepath) override;
		void Play(sound_id id, float volume) override;
		void Pause() override;
		void Resume() override;
		void Mute() override;
		void Unmute() override;
		void SetVolume(float volume) override;
	};

}

