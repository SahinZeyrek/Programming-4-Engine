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
		virtual void Play(const std::string& string) = 0;
		virtual void SetPause(bool setPause) = 0;
		virtual void SetMute(bool setMute) = 0;
		virtual void SetVolume(const float volume) = 0;
	};


}

