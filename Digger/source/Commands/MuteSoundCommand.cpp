#include "MuteSoundCommand.h"
#include "ServiceLocator.h"
void dae::MuteSoundCommand::Execute()
{
	if (!m_IsMuted)
	{
		ServiceLocator::GetSoundSystem().Mute();
		m_IsMuted = true;
	}
	else
	{
		ServiceLocator::GetSoundSystem().Unmute();
		m_IsMuted = false;
	}

}
