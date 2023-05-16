#pragma once
#include "ISoundSystem.h"
namespace dae
{
	class NullSoundSys final : public ISoundSystem
	{
	public:
		virtual ~NullSoundSys() override = default;
		virtual void Play(const sound_id id, const float volume) override;
		virtual void TogglePause(bool setPause) override;
		virtual void ToggleMute(bool setMute) override;
		virtual void SetVolume(const float volume) override;
		virtual void Load(const std::string& file) override;

	private:

	};



}

