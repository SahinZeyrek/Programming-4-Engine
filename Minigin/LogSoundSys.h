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
		virtual void Play(const std::string& string) override;
		virtual void SetPause(bool setPause) override;
		virtual void SetMute(bool setMute) override;
		virtual void SetVolume(const float volume) override;
	};

}

