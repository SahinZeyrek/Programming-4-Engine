#include "LogSoundSys.h"
#include "AudioManager.h"
#include <iostream>

namespace dae
{
	LogSoundSys::LogSoundSys(std::unique_ptr<ISoundSystem>&& sys) : m_realSS(std::move(sys))
	{

	}

	void LogSoundSys::Play(const std::string& string)
	{
		std::cout << "Playing: [" << string << "]\n";
		m_realSS->Play(string);
	}

	void LogSoundSys::SetPause(bool setPause)
	{
		m_realSS->SetPause(setPause);
		std::cout << "Pausing audio \n";
	}

	void LogSoundSys::SetMute(bool setMute)
	{
		m_realSS->SetMute(setMute);
		std::cout << "Muting Audio \n";
	}

	void LogSoundSys::SetVolume(const float volume)
	{
		m_realSS->SetVolume(volume);
		std::cout << "Setting Volume to " << volume << '\n';
	}
}

