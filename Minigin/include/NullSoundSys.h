#pragma once
#include "ISoundSystem.h"
namespace dae
{
	class NullSoundSys final : public ISoundSystem
	{
	public:
		virtual ~NullSoundSys() = default;
		virtual void Play(const std::string& path) override;
		virtual void SetPause(bool setPause) override;
		virtual void SetMute(bool setMute) override;
		virtual void SetVolume(const float volume) override;

	private:

	};



}
