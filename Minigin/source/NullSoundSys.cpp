#include "NullSoundSys.h"
#include "iostream"
namespace dae
{
	void NullSoundSys::Play(const sound_id , const float )
	{
		std::cout << "DEFAULT SOUND SYSTEM\n";
	}

	void NullSoundSys::TogglePause(bool)
	{
		std::cout << "DEFAULT SOUND SYSTEM\n";
	}

	void NullSoundSys::ToggleMute(bool)
	{
		std::cout << "DEFAULT SOUND SYSTEM\n";
	}

	void NullSoundSys::SetVolume(const float)
	{
		std::cout << "DEFAULT SOUND SYSTEM\n";
	}

	void NullSoundSys::Load(const std::string& file)
	{
		std::cout << "DEFAULT SOUND SYSTEM\n";
	}
}

