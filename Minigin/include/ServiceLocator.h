#pragma once

#include <memory>

#include "sound/NullSoundSys.h"

namespace dae
{
	class ServiceLocator final
	{
		static std::unique_ptr<ISoundSystem> m_SS_Instance;

	public:
		static ISoundSystem& GetSoundSystem();
		static void RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& sys);
	};
}


