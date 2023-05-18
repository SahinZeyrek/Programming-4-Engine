#include "ServiceLocator.h"

namespace dae
{
	/* static */ std::unique_ptr<ISoundSystem> ServiceLocator::m_SS_Instance{ std::make_unique<NullSoundSys>() };

	/* static */ ISoundSystem& ServiceLocator::GetSoundSystem()
	{
		return *m_SS_Instance;
	}

	/* static */ void ServiceLocator::RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& sys)
	{
		m_SS_Instance = (sys == nullptr) ? std::make_unique<NullSoundSys>() : std::move(sys);
	}
}