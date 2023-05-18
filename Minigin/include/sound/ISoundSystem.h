#pragma once

#include  <string>

namespace dae
{
	// INTERFACE
	using sound_id = unsigned short;
	class ISoundSystem
	{
	public:
		virtual ~ISoundSystem() = default;
		virtual sound_id AddSound(std::string_view filepath) = 0;
		virtual void Play(sound_id id, float volume) = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;
		virtual void Mute() = 0;
		virtual void Unmute() = 0;
		virtual void SetVolume(float volume) = 0;
	};
}

