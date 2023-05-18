#pragma once
#include "ISoundSystem.h"
namespace dae
{
	class NullSoundSys final : public ISoundSystem
	{
	public:
		virtual ~NullSoundSys() = default;

		sound_id AddSound(std::string_view) override { return 0; }
		void Play(sound_id, float) override {}
		void Pause() override {}
		void Resume() override {}
		void Mute() override {}
		void Unmute() override {}
		void SetVolume(float) override {}
	};
}

