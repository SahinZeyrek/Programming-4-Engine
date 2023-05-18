#include "sound/LogSoundSys.h"
#include <iostream>

namespace dae
{
	LogSoundSys::LogSoundSys(std::unique_ptr<ISoundSystem>&& sys)
		: m_realSS(std::move(sys))
	{

	}

	sound_id LogSoundSys::AddSound(std::string_view filepath)
	{
		sound_id id = m_realSS->AddSound(filepath);
		std::cout << "Adding sound '" << filepath << "' with id " << id << '\n';
		return id;
	}

	void LogSoundSys::Play(sound_id id, float volume)
	{
		m_realSS->Play(id, volume);
		std::cout << "Playing sound " << id << " with " << volume * 100 << "% volume\n";
	}

	void LogSoundSys::Pause()
	{
		m_realSS->Pause();
		std::cout << "Pausing audio\n";
	}

	void LogSoundSys::Resume()
	{
		m_realSS->Resume();
		std::cout << "Pausing audio\n";
	}

	void LogSoundSys::Mute()
	{
		m_realSS->Mute();
		std::cout << "Muting audio\n";
	}

	void LogSoundSys::Unmute()
	{
		m_realSS->Unmute();
		std::cout << "Unmuting audio\n";
	}

	void LogSoundSys::SetVolume(float volume)
	{
		m_realSS->SetVolume(volume);
		std::cout << "Setting global volume to " << volume * 100 << "%\n";
	}

}

